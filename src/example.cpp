#include "../include/example.h"

using namespace std;

/*********************************\
| Several example to test all the |
| cases in the simplex algorithm  |
\*********************************/


/// Everything is good (a solution, feasible domain)

vector<Rational> line1 = { Rational(5), Rational(-2),  Rational(-3), Rational(-1), Rational(-1), Rational(0), Rational(0) };
vector<Rational> line2 = { Rational(11), Rational(-4),  Rational(-1), Rational(-2), Rational(0), Rational(-1), Rational(0) };
vector<Rational> line3 = { Rational(8), Rational(-3),  Rational(-4), Rational(-2), Rational(0), Rational(0), Rational(-1) };
vector<Rational> z = { Rational(0), Rational(5), Rational(4), Rational(3), Rational(0), Rational(0), Rational(0) };
vector<vector<Rational>> ex_dico = { z , line1, line2, line3 };
vector<string> ex_names = { "z", "x_1", "x_2", "x_3", "x_4", "x_5", "x_6" };
vector<unsigned int> ex_basic_vars = {0,4,5,6};

Dictionnary example(ex_dico, ex_names, ex_basic_vars);

/// Example of unbounded domain

vector<Rational> unbound_constr = { Rational(4), Rational(-1), Rational(1), Rational(-1) };
vector<Rational> unbounded_z = { Rational(0), Rational(1), Rational(1), Rational(0) };
vector<vector<Rational>> unbounded_dico = {unbounded_z, unbound_constr};
vector<string> unbounded_names = {"z","x_1","x_2","x_3"};
vector<unsigned int> unbounded_basic_var = {0,3};

Dictionnary unbounded(unbounded_dico, unbounded_names, unbounded_basic_var);

/// Example of a non feasible domain (ie (0,0,...,0) not in the domain)

vector<Rational> line1_ = { Rational(-2), Rational(2), Rational(-1), Rational(-1), Rational(0), Rational(0) };
vector<Rational> line2_= { Rational(-2), Rational(-1), Rational(2), Rational(0), Rational(-1), Rational(0) };
vector<Rational> line3_ = { Rational(7), Rational(-1), Rational(-1), Rational(0), Rational(0), Rational(-1) };
vector<Rational> z_ = { Rational(0), Rational(2), Rational(1), Rational(0), Rational(0), Rational(0) };
vector<vector<Rational>> dico_non_feasible = { z_ , line1_, line2_, line3_ };
vector<string> names_non_feasible = { "z", "x_1", "x_2", "x_3", "x_4", "x_5" };
vector<unsigned int> basic_vars_non_feas = {0,3,4,5};

Dictionnary nonFeasible(dico_non_feasible, names_non_feasible, basic_vars_non_feas);
