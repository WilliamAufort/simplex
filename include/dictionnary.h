#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include "rational.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

class Dictionnary
{
    public:
        enum quantifier { GREATER, LOWER, EQUAL} ; /// For parser

        Dictionnary(): dico(std::vector<std::vector<Rational>>()), basic_vars(std::vector<unsigned int>()), names(std::vector<std::string>()), latex(std::string()), nb_dico(0){};
        Dictionnary(std::vector<std::vector<Rational>> _dico, std::map<unsigned int, std::string> _names);
        Dictionnary(std::vector<std::vector<Rational>> _dico, std::vector<std::string> _names, std::vector<unsigned int> _basic_vars): dico(_dico), basic_vars(_basic_vars),names(_names), latex(std::string()), nb_dico(0) {};
        ~Dictionnary() {};

        /// The classical functions

        unsigned int findEnteringVariable() __attribute__((pure));
        unsigned int findPivot(unsigned int entering) __attribute__((pure));
        void divideAll(unsigned int entering, unsigned int pivot);
        void addToAllLines(unsigned int entering, unsigned int pivot);
        bool oneStep(bool verbose);

        /// In the case where the domain is not feasible

        bool emptyDomain() __attribute__((pure));
        void add_x0_variable();
        unsigned int findIllegalPivot() __attribute__((pure));
        void illegalStep(bool verbose);
        void firstRound(bool verbose);

        /// General solver

        std::vector<Rational> solution();
        void solve(bool verbose);

        /// Printers (LaTeX essentially)

        friend std::ostream& operator <<(std::ostream& flux, Dictionnary const& dictio);
        void stupidPrinter();
        void printLaTeXHeader();
        void printDicoLaTeX ();
        unsigned int findPivotLaTeX(unsigned int entering);
        bool oneStepLaTeX(bool verbose);
        void illegalStepLaTeX(bool verbose);
        void firstRoundLaTeX(bool verbose);
        void solveLaTeX(bool verbose);
        void saveCodeLaTeX(std::string fileName);

        /// Attributes

        std::vector<std::vector<Rational>> dico;
        std::vector<unsigned int> basic_vars;
        std::vector<std::string> names; /// the real names of the different variables
        std::string latex; /// LaTeX output
        int nb_dico; /// Number of the dictionnary we are considering (useful in latex printers)
    private:
};

#endif
