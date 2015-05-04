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
    ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout << endl<<"Syntaxes :" << endl;
        cout << "   ./simplex (-i file.lp) (-l output.tex) (-v)" << endl << endl;
        cout << "-i               Input (.lp file)" << endl;
        cout << "-l               Output a LaTeX description of the dictionnaries" << endl;
        cout << "-v               Verbose" << endl;
        cout << "-h               You are here" << endl;
        cout << "--help           You are here" << endl << endl;
        return EXIT_SUCCESS;
    }

    Dictionnary dico;

    if (arguments.getOption("i"))
        dico = parseDictionnaryFile(arguments.getArgument(0));
    else
        dico = unbounded; /// If you want another example, change here

    if (arguments.getOption("l"))
    {
        dico.solveLaTeX(arguments.getOption("v"));
        dico.saveCodeLaTeX(arguments.getArgument(0));
        cout << "LaTeX writting successfully performed in " << arguments.getArgument(1) << endl;
    }
    else
    {
        dico.solve(arguments.getOption("v"));
    }
	return EXIT_SUCCESS;
}
