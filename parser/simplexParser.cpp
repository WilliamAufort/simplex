// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 5 "parser/parser.y" // lalr1.cc:399


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

void update(std::vector<std::vector<Rational>> dico)
{
    unsigned int old_n = static_cast<unsigned int>(dico[0].size());
    unsigned int old_m = static_cast<unsigned int>(dico.size()) -1 ;
    std::cout << "resize : " << old_n + old_m << std::endl;
    for (unsigned int constraint = 0; constraint < dico.size(); ++constraint)
        dico[constraint].resize(old_n + old_m,Rational(0));
    for (unsigned int constraint = 1; constraint < dico.size(); ++constraint)
        dico[constraint][old_n+constraint] = Rational(-1);
}


#line 113 "parser/simplexParser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "simplexParser.hpp"

// User implementation prologue.

#line 127 "parser/simplexParser.cpp" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 116 "parser/parser.y" // lalr1.cc:474
namespace SimplexParser {
#line 213 "parser/simplexParser.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 125 "parser/parser.y" // lalr1.cc:847
    { driver.setResult(*(yystack_[1].value.dictio)); }
#line 662 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 129 "parser/parser.y" // lalr1.cc:847
    { update(dico); (yylhs.value.dictio) = new Dictionnary(dico,names); }
#line 668 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 133 "parser/parser.y" // lalr1.cc:847
    { dico.push_back(*((yystack_[0].value.vect)));}
#line 674 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 5:
#line 134 "parser/parser.y" // lalr1.cc:847
    { reverse((yystack_[0].value.vect)); dico.push_back(*(yystack_[0].value.vect)); }
#line 680 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 138 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.vect) = new std::vector<Rational>(1,Rational(0)); inserer((yystack_[0].value.paire),(yylhs.value.vect));}
#line 686 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 139 "parser/parser.y" // lalr1.cc:847
    { inserer((yystack_[1].value.paire),(yystack_[0].value.vect)); delete (yystack_[1].value.paire); (yylhs.value.vect) = (yystack_[0].value.vect);}
#line 692 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 143 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.vect) = new std::vector<Rational>(1,Rational(0)); inserer((yystack_[0].value.paire),(yylhs.value.vect)); delete (yystack_[0].value.paire);}
#line 698 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 144 "parser/parser.y" // lalr1.cc:847
    { inserer((yystack_[1].value.paire),(yystack_[0].value.vect)); delete (yystack_[1].value.paire); (yylhs.value.vect) = (yystack_[0].value.vect); }
#line 704 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 148 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.paire) = new std::pair<unsigned int, Rational>(0,Rational((yystack_[0].value.reel)));}
#line 710 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 149 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.paire) = new std::pair<unsigned int, Rational>(0,Rational((yystack_[0].value.reel)));}
#line 716 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 150 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.paire) = new std::pair<unsigned int, Rational>(0,Rational(-(yystack_[0].value.reel)));}
#line 722 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 151 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(1));}
#line 728 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 152 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(1));}
#line 734 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 153 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(-1));}
#line 740 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 154 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational((yystack_[1].value.reel)));}
#line 746 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 155 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(-(yystack_[1].value.reel)));}
#line 752 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 158 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.paire) = new std::pair<unsigned int, Rational>(0,Rational((yystack_[0].value.reel)));}
#line 758 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 159 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.paire) = new std::pair<unsigned int, Rational>(0,Rational(-(yystack_[0].value.reel)));}
#line 764 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 160 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(1));}
#line 770 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 161 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(-1));}
#line 776 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 162 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational((yystack_[1].value.reel)));}
#line 782 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 163 "parser/parser.y" // lalr1.cc:847
    { if (map_names.find(*(yystack_[0].value.str)) == map_names.end()) { map_names[*(yystack_[0].value.str)] = n; names[n] = *(yystack_[0].value.str); n++;} (yylhs.value.paire) = new std::pair<unsigned int, Rational>(map_names[*(yystack_[0].value.str)],Rational(-(yystack_[1].value.reel)));}
#line 788 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 167 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.returnValue) = (yystack_[0].value.returnValue); }
#line 794 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 168 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.returnValue) = (yystack_[0].value.returnValue) + (yystack_[1].value.returnValue);}
#line 800 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 172 "parser/parser.y" // lalr1.cc:847
    { inserer(new std::pair<unsigned int, Rational>(0,Rational(-(yystack_[0].value.reel))),(yystack_[2].value.vect)); insertConstraint((yystack_[2].value.vect),(yystack_[1].value.quant)); (yylhs.value.returnValue) = 0;}
#line 806 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 176 "parser/parser.y" // lalr1.cc:847
    {}
#line 812 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 177 "parser/parser.y" // lalr1.cc:847
    {}
#line 818 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 181 "parser/parser.y" // lalr1.cc:847
    {}
#line 824 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 182 "parser/parser.y" // lalr1.cc:847
    {}
#line 830 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 186 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.quant) = Dictionnary::GREATER; }
#line 836 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 187 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.quant) = Dictionnary::LOWER; }
#line 842 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 188 "parser/parser.y" // lalr1.cc:847
    { (yylhs.value.quant) = Dictionnary::EQUAL; }
#line 848 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 192 "parser/parser.y" // lalr1.cc:847
    {}
#line 854 "parser/simplexParser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 193 "parser/parser.y" // lalr1.cc:847
    {}
#line 860 "parser/simplexParser.cpp" // lalr1.cc:847
    break;


#line 864 "parser/simplexParser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -44;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      -8,     1,     1,    26,    27,    16,    25,   -44,     3,    11,
     -44,     8,   -44,   -44,   -44,     1,   -44,   -44,   -44,    28,
     -44,    15,    17,   -44,     8,     6,    18,     1,   -44,    29,
     -44,    30,   -44,   -44,   -44,   -44,   -44,    32,    19,   -44,
     -44,   -44,   -44,     6,     6,    22,    19,    33,    35,    36,
     -44,     6,   -44,    36,    24,    38,   -44,   -44,   -44
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,    10,    13,     0,     0,
       5,     6,     4,     1,     2,     0,    16,    11,    14,    12,
      15,     0,     0,     7,     8,     0,     0,    24,    17,    18,
      20,    19,    21,     9,    31,    32,    33,     0,     0,    25,
      22,    23,    26,     0,     0,     0,    27,     0,     0,     0,
      28,     0,    30,    35,     0,     0,    34,     3,    29
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -44,   -44,   -44,   -44,    23,    20,   -44,   -44,    21,   -44,
     -16,   -44,   -43,   -11
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    25,    23,    11,    24,    26,    27,
      45,    46,    37,    54
  };

  const unsigned char
  Parser::yytable_[] =
  {
      47,    48,     1,     2,     6,     7,    17,    18,    55,     8,
       9,    34,    35,    36,    19,    20,    21,    22,    29,    30,
      31,    32,    43,    44,    10,    12,    13,    14,    15,    16,
      50,    38,    28,    40,    41,    42,    49,    51,    52,    57,
      53,    58,    56,     0,    33,     0,     0,     0,    39
  };

  const signed char
  Parser::yycheck_[] =
  {
      43,    44,    10,    11,     3,     4,     3,     4,    51,     8,
       9,     5,     6,     7,     3,     4,     8,     9,     3,     4,
       3,     4,     3,     4,     1,     2,     0,     0,    12,     4,
      46,    13,     4,     4,     4,     3,    14,     4,     3,    15,
       4,     3,    53,    -1,    24,    -1,    -1,    -1,    27
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    10,    11,    18,    19,    20,     3,     4,     8,     9,
      21,    23,    21,     0,     0,    12,     4,     3,     4,     3,
       4,     8,     9,    22,    24,    21,    25,    26,     4,     3,
       4,     3,     4,    22,     5,     6,     7,    29,    13,    25,
       4,     4,     3,     3,     4,    27,    28,    29,    29,    14,
      27,     4,     3,     4,    30,    29,    30,    15,     3
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    17,    18,    19,    20,    20,    21,    21,    22,    22,
      23,    23,    23,    23,    23,    23,    23,    23,    24,    24,
      24,    24,    24,    24,    25,    25,    26,    27,    27,    28,
      28,    29,    29,    29,    30,    30
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     8,     2,     2,     1,     2,     1,     2,
       1,     2,     2,     1,     2,     2,     2,     3,     2,     2,
       2,     2,     3,     3,     1,     2,     3,     1,     2,     5,
       3,     1,     1,     1,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "TEOF", "error", "$undefined", "FLOAT", "NAME", "GREATER_EQ",
  "LOWER_EQ", "EQUAL", "PLUS", "MINUS", "MINIMIZE", "MAXIMIZE", "ST",
  "BOUNDS", "VARIABLES", "END", "END_OF_FILE", "$accept", "input",
  "expression", "objectif", "expr", "expr_end", "init_term", "term",
  "constraints", "constraint", "bounds", "bound", "operator", "variables", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   125,   125,   129,   133,   134,   138,   139,   143,   144,
     148,   149,   150,   151,   152,   153,   154,   155,   158,   159,
     160,   161,   162,   163,   167,   168,   172,   176,   177,   181,
     182,   186,   187,   188,   192,   193
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16
    };
    const unsigned int user_token_number_max_ = 271;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 116 "parser/parser.y" // lalr1.cc:1155
} // SimplexParser
#line 1312 "parser/simplexParser.cpp" // lalr1.cc:1155
#line 196 "parser/parser.y" // lalr1.cc:1156


void SimplexParser::Parser::error(const location_type& loc, const std::string& m)
{
	int location = loc.begin.line;
	std::ostringstream out;
	out << "Ligne " << location << " : " << m;
	throw ParseError(out.str());
}
