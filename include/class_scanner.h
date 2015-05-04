#ifndef DEF_CLASS_SCANNER
#define DEF_CLASS_SCANNER

#if ! defined(yyFlexLexerOnce)
	#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
namespace MC {

class Scanner : public yyFlexLexer {
	public:
		Scanner(std::istream *in) : yyFlexLexer(in), yylval(nullptr) {};
		int yylex(MC::MC_Parser::semantic_type *lval)
		{
			yylval = lval;
			return(yylex());
		}

	private:
	/* hide this one from public view */
	int yylex();
	/* yyval ptr */
	MC::Parser::semantic_type *yylval;
};

}
#endif
