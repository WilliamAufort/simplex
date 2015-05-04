%option yylineno
%option c++
%option prefix="SimplexParser"

%{

namespace SimplexParser
{
	class Driver;
}

#include "simplexParser.hpp"
#include "lexer.h"
typedef SimplexParser::Parser::token token;
typedef SimplexParser::Parser::token_type token_type;
#define yyterminate() return token::TEOF

%}

%s line_comment comment
%%

">="                        return (token::GREATER_EQ);
"<="                    	return (token::LOWER_EQ);
"="	                    	return (token::EQUAL);

"+"                     	return (token::PLUS);
"-"                     	return (token::MINUS);

"MINIMIZE"					return (token::MINIMIZE);
"MAXIMIZE"					return (token::MAXIMIZE);
"SUBJECT TO"				return (token::ST);
"BOUNDS"					return (token::BOUNDS);
"VARIABLES"					return (token::VARIABLES);
"END"                       return (token::END);


"//"                        BEGIN(line_comment);
<line_comment>"\n"          BEGIN(INITIAL);
<line_comment>"eof"         return (token::END_OF_FILE);
<line_comment>.             break;



"/*"                        BEGIN(comment);
<comment>"\*"               BEGIN(INITIAL);
<comment>"eof"       	    return (token::END_OF_FILE);
<comment>.                  break;

[ \t\n\r]+	    	    	break;		/* ignore white space */


[0-9]+("."[0-9]+)?          {
								yylval->reel = atoi(yytext);
                            	return (token::FLOAT);
                            }

[A-Za-z_]([A-Za-z0-9_])*	{
                             	yylval->str = new std::string(yytext);
                             	return (token::NAME);
                            }
