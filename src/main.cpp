#include "../include/rational.h"
#include "../include/dictionnary.h"
#include "../include/example.h"
#include "../include/argumentsParseur.h"
#include "../parser/driver.h"

#include <fstream>

extern Dictionnary example;
extern Dictionnary unbounded;
extern Dictionnary nonFeasible;

using namespace std;

Dictionnary parseDictionnaryFile(string fileName);

Dictionnary parseDictionnaryFile(string fileName)
{
    SimplexParser::Driver parserDriver;
    try
    {
        return parserDriver.parse(fileName);
    }
    catch (ParseError& e)
    {
        cerr << e.getMessage() << endl;
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage : ./simplex file.lp" << endl;
        return (EXIT_FAILURE);
    }

    ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
    arguments.parse(argc, argv);
    Dictionnary dico = parseDictionnaryFile(arguments.getArgument(0));
    dico.stupidPrinter();

    if(arguments.demandeAide())
    {
        cout << endl<<"Syntaxes :" << endl;
        cout << "   ./simplex (-i file.lp) (-l output.tex) (-v)" << endl << endl;
        cout << "-l               Output a LaTeX description of the dictionnaries" << endl;
        cout << "-v               Verbose" << endl;
        cout << "-h               You are here" << endl;
        cout << "--help           You are here" << endl << endl;
        return EXIT_SUCCESS;
    }

    Dictionnary dico;

    if (arguments.getOption("i"))
    {
        ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
        arguments.parse(argc, argv);
        dico = parseDictionnaryFile(arguments.getArgument(0));
        dico.stupidPrinter();
    }
    else
        dico = unbounded; /// If you want another example, change here

    if (arguments.getOption("l"))
    {
        unbounded.solveLaTeX(arguments.getOption("v"));
        unbounded.saveCodeLaTeX(arguments.getArgument(0));
        cout << "LaTeX writting successfully performed in " << arguments.getArgument(1) << endl;
    }
    else
    {
        unbounded.solve(arguments.getOption("v"));
    }
	return EXIT_SUCCESS;
}
