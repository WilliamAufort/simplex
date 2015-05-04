%code requires {
	#include "../include/dictionnary.h"
}

%{

namespace SimplexParser
{
	class Driver;
}

#include <sstream>
#include <list>
#include <map>
#include "simplexParser.hpp"
#include "lexer.h"
#include "driver.h"
#include "../include/ParseError.h"

#define yylex driver.lexer->yylex

int n = 1; // number of variables + 1
int m = 0; // number of constraints
std::map<std::string,unsigned int> map_names; /// A map for the names of the variables
std::map<unsigned int,std::string> names;
std::vector<std::vector<Rational>> dico;

void inserer(std::pair<unsigned int,Rational>* paire, std::vector<Rational>* expression)
{
    if (paire->first >= expression->size())
        expression->resize(paire->first+1,Rational(0));

    (*expression)[paire->first] = paire->second;
}

void reverse(std::vector<Rational>* expression)
{
    for (unsigned int i = 0; i < expression->size(); ++i)
        (*expression)[i] = - (*expression)[i];
}

void insertConstraint(std::vector<Rational>* expression, Dictionnary::quantifier q)
{
    switch (q)
    {
        case Dictionnary::GREATER :
        {
            dico.push_back(*expression);
            break;
        }
        case Dictionnary::LOWER :
        {
            reverse(expression);
            dico.push_back(*expression);
            break;
        }
        case Dictionnary::EQUAL :
        {
            dico.push_back(*expression);
            reverse(expression);
            dico.push_back(*expression);
            break;
        }
    }
    m++;
    delete expression;
}

void update(std::vector<std::vector<Rational>>& dico)
{
    unsigned int old_m = static_cast<unsigned int>(dico.size()) -1 ;
    for (unsigned int constraint = 0; constraint < dico.size(); ++constraint)
        dico[constraint].resize(n + old_m,Rational(0));
    for (unsigned int constraint = 1; constraint < dico.size(); ++constraint)
        dico[constraint][n+constraint-1] = Rational(-1);
}

%}

%union
{
	std::string* str;
	int reel;
	Dictionnary* dictio;
	std::pair<unsigned int,Rational>* paire;
	std::vector<Rational>* vect;
	Dictionnary::quantifier quant;
	int returnValue;
}

%type <dictio> expression
%type <paire> term init_term
%type <vect> expr expr_end
%type <quant> operator;
%type <returnValue> constraint constraints

%token TEOF 0
%token <reel> FLOAT
%token <str> NAME

%token GREATER_EQ LOWER_EQ EQUAL
%token PLUS MINUS

%token MINIMIZE MAXIMIZE
%token ST
%token BOUNDS
%token VARIABLES
%token END
%token END_OF_FILE

%start input

%language "C++"
%define api.namespace {SimplexParser}
%define parse.error verbose
%define parser_class_name {Parser}
%parse-param {Driver &driver}
%locations

%%

input:
	expression TEOF { driver.setResult(*$1); }
;

expression:
	objectif ST constraints BOUNDS bounds VARIABLES variables END { update(dico); $$ = new Dictionnary(dico,names); }
;

objectif:
 	  MAXIMIZE expr { dico.push_back(*($2));}
	| MINIMIZE expr { reverse($2); dico.push_back(*$2); }
;

expr:
	    init_term           { $$ = new std::vector<Rational>(1,Rational(0)); inserer($1,$$);}
	  | init_term expr_end  { inserer($1,$2); delete $1; $$ = $2;}
;

expr_end:
      term              { $$ = new std::vector<Rational>(1,Rational(0)); inserer($1,$$); delete $1;}
	| term expr_end	    { inserer($1,$2); delete $1; $$ = $2; }
;

init_term:
      FLOAT                 { $$ = new std::pair<unsigned int, Rational>(0,Rational($1));}
    | PLUS FLOAT			{ $$ = new std::pair<unsigned int, Rational>(0,Rational($2));}
    | MINUS FLOAT           { $$ = new std::pair<unsigned int, Rational>(0,Rational(-$2));}
    | NAME                  { if (map_names.find(*$1) == map_names.end()) { map_names[*$1] = n; names[n] = *$1; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$1],Rational(1));}
    | PLUS NAME 			{ if (map_names.find(*$2) == map_names.end()) { map_names[*$2] = n; names[n] = *$2; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$2],Rational(1));}
    | MINUS NAME            { if (map_names.find(*$2) == map_names.end()) { map_names[*$2] = n; names[n] = *$2; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$2],Rational(-1));}
    | FLOAT NAME            { if (map_names.find(*$2) == map_names.end()) { map_names[*$2] = n; names[n] = *$2; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$2],Rational($1));}
    | MINUS FLOAT NAME      { if (map_names.find(*$3) == map_names.end()) { map_names[*$3] = n; names[n] = *$3; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$3],Rational(-$2));}

term:
	  PLUS FLOAT			{ $$ = new std::pair<unsigned int, Rational>(0,Rational($2));}
    | MINUS FLOAT			{ $$ = new std::pair<unsigned int, Rational>(0,Rational(-$2));}
	| PLUS NAME 			{ if (map_names.find(*$2) == map_names.end()) { map_names[*$2] = n; names[n] = *$2; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$2],Rational(1));}
	| MINUS NAME			{ if (map_names.find(*$2) == map_names.end()) { map_names[*$2] = n; names[n] = *$2; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$2],Rational(-1));}
	| PLUS FLOAT NAME   	{ if (map_names.find(*$3) == map_names.end()) { map_names[*$3] = n; names[n] = *$3; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$3],Rational($2));}
	| MINUS FLOAT NAME	    { if (map_names.find(*$3) == map_names.end()) { map_names[*$3] = n; names[n] = *$3; n++;} $$ = new std::pair<unsigned int, Rational>(map_names[*$3],Rational(-$2));}
;

constraints:
      constraint { $$ = $1; }
    | constraint constraints { $$ = $2 + $1;}
;

constraint:
	    expr operator FLOAT { inserer(new std::pair<unsigned int, Rational>(0,Rational(-$3)),$1); insertConstraint($1,$2); $$ = 0;}
;

bounds:
      bound         {}
    | bound bounds  {}
;

bound:
	  FLOAT operator NAME operator FLOAT {}
	| NAME operator FLOAT				 {}
;

operator:
	  GREATER_EQ		{ $$ = Dictionnary::GREATER; }
	| LOWER_EQ			{ $$ = Dictionnary::LOWER; }
	| EQUAL			    { $$ = Dictionnary::EQUAL; }
;

variables: // don't care
	  NAME variables	{}
	| NAME				{}
;

%%

void SimplexParser::Parser::error(const location_type& loc, const std::string& m)
{
	int location = loc.begin.line;
	std::ostringstream out;
	out << "Ligne " << location << " : " << m;
	throw ParseError(out.str());
}
