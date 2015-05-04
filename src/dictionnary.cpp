#include "../include/dictionnary.h"
#include "../include/std.h"
#include <algorithm>

using namespace std;

Dictionnary::Dictionnary(vector<vector<Rational>> _dico, map<unsigned int,string> _names)
: dico(_dico), basic_vars(vector<unsigned int>()), names(vector<string>()), latex(string()), nb_dico(0)
{
    /// init names
    for (unsigned int i = 1; i <= _names.size(); ++i)
        names.push_back(_names[i]);

    /// dico[0].size() = n + m + 1
    /// dico.size() = m (nb of constraints) + 1 (z)

    unsigned int n = static_cast<unsigned int>(dico[0].size() - dico.size()); /// n number of variables
    basic_vars.push_back(0); /// case of z
    for (unsigned int i = 1; i < dico.size(); ++i)
    {
        basic_vars.push_back(n+i);
    }
}

/// Find the entering variable = the first positive coeff in the first raw

unsigned int Dictionnary::findEnteringVariable()
{
    for (unsigned int i = 1; i < dico[0].size(); ++i)
    {
        if (dico[0][i] > Rational(0))
            return i;
    }
    return 0;
}

/// Find the good pivot corresponding to the entering variable given

unsigned int Dictionnary::findPivot(unsigned int entering)
{
    /// Build the limitations on the variable
    vector<pair<Rational,unsigned int>> limits;
    for (unsigned int i = 1; i < dico.size(); ++i)
        if (dico[i][entering] != 0)
        {
            Rational candidate = - dico[i][0] / dico[i][entering];
            if ((candidate > 0) || ((dico[i][0] == 0) && (dico[i][entering] < 0))) /// Special case for zero
                limits.push_back(pair<Rational,unsigned int>(candidate,i));
        }

    /// if no limitations, raise "Unbounded"
    if (limits.size() == 0)
    {
        throw "Unbounded domain";
    }

    /// Find the minimum positive value (in the case of legal pivot)
    unsigned int pivot = limits[0].second;
    Rational minimum = limits[0].first;
    for (unsigned int i = 1; i < limits.size(); ++i)
        if (limits[i].first < minimum)
        {
            pivot = limits[i].second;
            minimum = limits[i].first;
        }
    return pivot;
}

/// Modify the dictionnary with regard to the pivot

void Dictionnary::divideAll(unsigned int entering, unsigned int pivot)
{
    Rational factor = dico[pivot][entering];
    for (unsigned int var = 0; var < dico[0].size(); ++var)
        dico[pivot][var] /= - factor;
}

void Dictionnary::addToAllLines(unsigned int entering, unsigned int pivot)
{
    for (unsigned int line = 0; line != dico.size(); ++line)
        if (line != pivot)
        {
            Rational factor = dico[line][entering];
            for (unsigned int var = 0; var < dico[0].size(); ++var)
                dico[line][var] += factor * dico[pivot][var];
        }
}

/// One the step of the simplex algorithm

bool Dictionnary::oneStep(bool verbose)
{
    unsigned int var = findEnteringVariable();
    if (var == 0)
    {
        if (verbose)
            cout << "Cannot improve " << names[0] << endl;
        return 0;
    }
    else
    {
        if (verbose)
            cout << "The entering variable is : " << names[var] << endl;
        unsigned int pivot = findPivot(var);
        if (verbose)
            cout << "The pivot is : " << names[pivot] << endl;
        divideAll(var, pivot);
        addToAllLines(var,pivot);
        basic_vars[pivot] = var;
        if (verbose)
            cout << "New dictionnary after this step : " << endl << *this << endl;
        return 1;
    }
}

/// See if the initial domain is empty

bool Dictionnary::emptyDomain()
{
    for (unsigned int i = 1; i < dico.size(); ++i)
    {
        if (dico[i][0] < 0)
            return 1;
    }
    return 0;
}

/// If the domain is empty, add a new variable x0

void Dictionnary::add_x0_variable()
{
    for (unsigned int i = 1; i < dico.size(); ++i)
    {
        dico[i].push_back(Rational(1));
    }
    /// Change the objective function
    /// Be careful ! You will have to save it before this step

    for (unsigned int i = 0; i < dico[0].size(); ++i)
    {
        dico[0][i] = Rational(0);
    }
    dico[0].push_back(Rational(-1));
    names.push_back("x_0");
}

/// Find the illegal pivot corresponding to the last variable
/// This function is much more simpler that the classical findPivot.
/// Indeed, all the constraints provides "limits" and we just have to
/// take the minimum negative value.

unsigned int Dictionnary::findIllegalPivot()
{
    unsigned int pivot = 1;
    Rational minimum = dico[1][0];
    for (unsigned int i = 2; i < dico.size(); ++i)
        if (dico[i][0] < minimum)
        {
            pivot = i;
            minimum = dico[i][0];
        }
    return pivot;
}

void Dictionnary::illegalStep(bool verbose)
{
    add_x0_variable();
    unsigned int var = static_cast<unsigned int>(dico[0].size()-1);
    unsigned int pivot = findIllegalPivot();
    if (verbose)
            cout << "The pivot is " << names[pivot] << endl;
    divideAll(var, pivot);
    addToAllLines(var,pivot);
    basic_vars[pivot] = var;
    if (verbose)
        cout << "New dictionnary after this step : " << endl << *this << endl;
}

void Dictionnary::firstRound(bool verbose)
{
    if (verbose)
        cout << "The domain is not currently feasible" << endl;
    vector<Rational> initial_objective = dico[0]; /// Keep it in memory

    /// First step (illegal pivot)
    illegalStep(verbose);

    /// Solve the auxillary programm
    while(oneStep(verbose)) {};

    /// If negative value of the objective function, the domain is empty
    if (dico[0][0] < 0)
        throw "Empty domain";

    /// Remove x0
    for (unsigned int i = 1; i < dico.size(); ++i)
        dico[i].pop_back();

    /// Build the new objective function
    dico[0] = initial_objective;
    unsigned int n = static_cast<unsigned int>(dico[0].size() - dico.size());
    for (unsigned int i = 1; i < basic_vars.size(); ++i)
    {
        unsigned int basic_var = basic_vars[i];
        if (basic_var <= n)
        {
            Rational factor = dico[0][basic_var];
            for (unsigned int var = 0; var < dico[0].size(); ++var)
                dico[0][var] += factor * dico[i][var];
        }
    }
    if (verbose)
        cout << "New initial dictionnary : " << endl << *this << endl;
}

/// Recover the solution of the optimization problem

vector<Rational> Dictionnary::solution()
{
    unsigned int n = static_cast<unsigned int>(dico[0].size() - dico.size());
    vector<Rational> sol(n+1,Rational(0));
    sol[0] = dico[0][0];
    for (unsigned int i = 1; i < basic_vars.size(); ++i)
        if (basic_vars[i] <= n)
            sol[basic_vars[i]] = dico[i][0];
    return sol;
}

/// Solve and print the result

void Dictionnary::solve(bool verbose)
{
    try
    {
        if (emptyDomain())
            firstRound(verbose);
        while(oneStep(verbose)) {};
        vector<Rational> sol = solution();
        cout << "Solution :" << endl << "[ ";
        for (unsigned int i = 0; i < sol.size()-1; ++i)
            cout << names[i] << " = " << sol[i] << ", ";
        cout << names[sol.size()-1] << " = " << sol[sol.size()-1] << " ]" << endl;
    }
    catch (const char* message)
    {
        cerr << message << endl;
    }
}

/// Ugly printer for a dictionnary

ostream& operator <<(ostream& flux, Dictionnary const& dictio)
{
    flux << dictio.names[0] << " = ";
    if (dictio.dico[0][0] != 0)
        flux << " + " << dictio.dico[0][0] << " ";
    for (unsigned int i = 1; i < (dictio.dico[0].size()); ++i)
    {
        if (dictio.dico[0][i] != 0)
            flux << " + " << dictio.dico[0][i] << " " << dictio.names[i];
    }
    flux << endl;
    /// Print all constraints
    for (unsigned int constraint = 1; constraint < dictio.dico.size(); ++constraint)
    {
        flux << dictio.dico[constraint][0];
        for (unsigned int var = 1; var < (dictio.dico[constraint].size()); ++var)
        {
            flux << " + " << dictio.dico[constraint][var] << " " << dictio.names[var];
        }
        flux << " = 0 " << endl;
    }
    return flux;
}

/// Stupid printer (debug)

void Dictionnary::stupidPrinter()
{
    for (unsigned int i = 0; i < dico.size(); ++i)
    {
        for (unsigned int j = 0; j < dico[j].size(); ++j)
            cout << dico[i][j] << " ";
        cout << endl;
    }
}

/*********************************************************\
| LaTeX printers and variants of the previous functions   |
| (Written again because otherwise it's too ugly to read  |
| the code)                                               |
\*********************************************************/

void Dictionnary::printLaTeXHeader()
{
    latex += "\\documentclass{article} \n"
             "\\usepackage[utf8]{inputenc} \n"
             "\\usepackage{amsmath} \n"
             "\\usepackage{amssymb} \n"
             "\\usepackage{datetime} \n \n";

    latex += "\\title{The simplex algorithm execution} \n"
             "\\author{Simplex Algorithm} \n"
             "\\date{\\today ~-- \\currenttime} \n \n";

    latex += "\\begin{document} \n \n"
             "\\maketitle \n \n";

    latex += "Let's study the following dictionnary \n \n";
    printDicoLaTeX();
}

void Dictionnary::printDicoLaTeX ()
{
    latex += "\\[ \n"
             "(D_" + intToString(nb_dico) + "):\\qquad \\left \\{ \n"
             "\\begin{array}{rc*" + intToString(static_cast<int>(dico[0].size() - dico.size()+1)) + "{cr}} \n";

    /// Compute the non-basic variables
    vector<unsigned int> non_basic;
    vector<unsigned int> basics = basic_vars;
    sort(basics.begin(),basics.end());
    for (unsigned int var = 0; var < dico[0].size(); ++var)
        non_basic.push_back(var);
    int eraser = 0;
    for (unsigned int i = 0; i < basics.size(); ++i)
    {
        non_basic.erase(non_basic.begin()+basics[i]-eraser);
        eraser++;
    }

    /// Print constraints
    for (unsigned int constraint = 1; constraint < dico.size(); ++constraint)
    {
        latex += names[basic_vars[constraint]] + " & =";
        if (dico[constraint][non_basic[0]] != 0)
            printRationalLaTeX(latex,dico[constraint][0],1);
        else
            latex += "& & ";
        for (unsigned int var = 0; var < non_basic.size(); ++var)
        {
            if (dico[constraint][non_basic[var]] != 0)
            {
                printRationalLaTeX(latex,dico[constraint][non_basic[var]],1);
                latex += names[non_basic[var]] + " ";
            }
            else
            {
                latex += "& & ";
            }
        }
        latex += "\\\\ \n";
    }
    latex += "\\hline \n";
    latex += names[0] + " & =";
    if (dico[0][0] != 0)
        printRationalLaTeX(latex,dico[0][0],1);
    else
        latex += "& &";
    for (unsigned int var = 0; var < non_basic.size(); ++var)
    {
        if (dico[0][non_basic[var]] != 0)
        {
            printRationalLaTeX(latex,dico[0][non_basic[var]],1);
            latex += names[non_basic[var]] + " ";
        }
        else
        {
            latex += "& &";
        }
    }
    latex += "\\end{array} \\right. \n"
             "\\] \n \n";
}

/// After this, only copy/paste of previous functions with latex output added

unsigned int Dictionnary::findPivotLaTeX(unsigned int entering)
{
    /// Build the limitations on the variable
    vector<pair<Rational,unsigned int>> limits;
    for (unsigned int i = 1; i < dico.size(); ++i)
        if (dico[i][entering] != 0)
        {
            Rational candidate = - dico[i][0] / dico[i][entering];
            if ((candidate > 0) || ((dico[i][0] == 0) && (dico[i][entering] < 0))) /// Special case for zero
                limits.push_back(pair<Rational,unsigned int>(candidate,i));
        }

    /// if no limitations, raise "Unbounded"
    if (limits.size() == 0)
    {
        latex += "but we don't have any bound on it given by the dictionnary. So the domain is unbounded. \n \n"
                 "\\end{document}";
        throw "Unbounded domain";
    }

    /// Find the minimum positive value (in the case of legal pivot)
    unsigned int pivot = limits[0].second;
    Rational minimum = limits[0].first;
    for (unsigned int i = 1; i < limits.size(); ++i)
        if (limits[i].first < minimum)
        {
            pivot = limits[i].second;
            minimum = limits[i].first;
        }
    return pivot;
}

bool Dictionnary::oneStepLaTeX(bool verbose)
{
    unsigned int var = findEnteringVariable();
    if (var == 0)
    {
        if (verbose)
            cout << "Cannot improve " << names[0] << endl;
        latex += "Here we cannot improve the objective function $" + names[0] + "$. \n";
        return 0;
    }
    else
    {
        if (verbose)
            cout << "The entering variable is : " << names[var] << endl;
        latex += "$" + names[var] + "$ enters, ";
        unsigned int pivot = findPivotLaTeX(var);
        if (verbose)
            cout << "The pivot is : " << names[pivot] << endl;
        latex += "$" + names[basic_vars[pivot]] + "$ leaves. \n \n";
        divideAll(var, pivot);
        addToAllLines(var,pivot);
        basic_vars[pivot] = var;
        nb_dico++;
        if (verbose)
            cout << "New dictionnary after this step : " << endl << *this << endl;
        latex += "After this step, we get the new dictionnary : \n \n";
        printDicoLaTeX();
        return 1;
    }
}

void Dictionnary::illegalStepLaTeX(bool verbose)
{
    add_x0_variable();
    nb_dico++;
    latex += "We add a new variable $x_0$ and get the dictionnary : \n \n";
    printDicoLaTeX();
    unsigned int var = static_cast<unsigned int>(dico[0].size()-1);
    unsigned int pivot = findIllegalPivot();
    if (verbose)
            cout << "The pivot is " << names[pivot] << endl;
    latex += "$" + names[var] + "$ enters, $" + names[basic_vars[pivot]] + "$ leaves. \n \n";
    divideAll(var, pivot);
    addToAllLines(var,pivot);
    basic_vars[pivot] = var;
    nb_dico++;
    if (verbose)
        cout << "New dictionnary after this step : " << endl << *this << endl;
    latex += "After this step, we get the new dictionnary : \n \n";
    printDicoLaTeX();
}

void Dictionnary::firstRoundLaTeX(bool verbose)
{
    if (verbose)
        cout << "The domain is not currently feasible" << endl;
    latex += "The domain is not currently feasible. \n";
    vector<Rational> initial_objective = dico[0];
    illegalStepLaTeX(verbose);
    while(oneStepLaTeX(verbose)) {};

    if (dico[0][0] < 0)
    {
        latex += names[0] + " = ";
        printRationalLaTeX(latex,dico[0][0],0);
        latex += " < 0, the optimal value is negative, so the initial domain is empty. \n";
        throw "The domain is empty.";
    }

    for (unsigned int i = 1; i < dico.size(); ++i)
        dico[i].pop_back();

    dico[0] = initial_objective;
    unsigned int n = static_cast<unsigned int>(dico[0].size() - dico.size());
    for (unsigned int i = 1; i < basic_vars.size(); ++i)
    {
        unsigned int basic_var = basic_vars[i];
        if (basic_var <= n)
        {
            Rational factor = dico[0][basic_var];
            for (unsigned int var = 0; var < dico[0].size(); ++var)
                dico[0][var] += factor * dico[i][var];
        }
    }
    if (verbose)
        cout << "New initial dictionnary : " << endl << *this << endl;
    latex += "So we restart with the new dictionnary : \n \n";
    printDicoLaTeX();
}

void Dictionnary::solveLaTeX(bool verbose)
{
    try
    {
        printLaTeXHeader();
        if (emptyDomain())
            firstRoundLaTeX(verbose);
        while(oneStepLaTeX(verbose)) {};
        vector<Rational> sol = solution();
        cout << "Solution :" << endl << "[ ";
        for (unsigned int i = 0; i < sol.size()-1; ++i)
            cout << names[i] << " = " << sol[i] << ", ";
        cout << names[sol.size()-1] << " = " << sol[sol.size()-1] << " ]" << endl;

        latex += "At the end, we get the final solution : \n $$ \\left(";
        for (unsigned int i = 0; i < sol.size()-1; ++i)
        {
            latex += names[i] + " = ";
            printRationalLaTeX(latex,sol[i],0);
            latex += ", ";
        }
        latex += names[sol.size()-1] + " = ";
        printRationalLaTeX(latex,sol[sol.size()-1],0);
        latex += " \\right) $$ \n";

        latex += "\\end{document}";
    }
    catch (const char* message)
    {
        cerr << message << endl;
    }
}

void Dictionnary::saveCodeLaTeX(string fileName)
{
    ofstream file(fileName.c_str());
    if (file.is_open())
    {
        file << latex;
        file.close();
    }
    else
    {
        cerr << "Couldn't open file : " << fileName << endl;
    }
}

