#include "../include/rational.h"
#include "../include/std.h"
#include <iostream>

using namespace std;

/********************\
| Simplify fractions |
\********************/

int Rational::gcd(int a, int b)
{
	while(b != 0)
	{
		const int t = b;
		b = a%b;
		a = t;
	}
	return abs(a); /// deal with negative values
}

void Rational::simplify()
{
	int p = gcd(numerator, denominator);
	numerator /= p;
	denominator /= p;
	if (denominator < 0)
    {
        denominator = - denominator;
        numerator = -numerator;
    }
}

/**********\
| Printers |
\**********/

ostream& operator<<(ostream& flux, Rational const& q)
{
	q.affiche(flux);
	return flux;
}

void printRationalLaTeX (string& flux, Rational const& q, bool inDico)
{
    q.afficheLaTeX(flux, inDico);
}

void Rational::affiche(ostream& flux) const
{
	if (denominator == 1)
		flux << numerator;
	else
		flux << numerator << "/" << denominator;
}

void Rational::afficheLaTeX(string& latex, bool inDico) const
{
    if (inDico)
        latex += "& ";

    if (numerator < 0)
    {
        if (inDico)
            latex += "- &";
        if (denominator == 1)
        {
            if (numerator != -1)
                latex += intToString(-numerator);
        }
        else
            latex += "\\frac{" +  intToString(-numerator) + "}{" + intToString(denominator) + "}";
    }
    else
    {
        if (inDico)
            latex += "+ &";
        if (denominator == 1)
        {
            if (numerator != 1)
                latex += intToString(numerator);
        }
        else
            latex += "\\frac{" + intToString(numerator) + "}{" + intToString(denominator) + "}";
    }
}

/*************************\
| Arithmetical Operators  |
\*************************/

Rational& Rational::operator+=(Rational const& q)
{
	numerator = q.denominator * numerator + q.numerator * denominator;
	denominator *= q.denominator;
	simplify();
	return *this;
}

Rational& Rational::operator-=(Rational const& q)
{
	numerator = q.denominator * numerator - q.numerator * denominator;
	denominator *= q.denominator;
	simplify();
	return *this;
}

Rational& Rational::operator*=(Rational const& q)
{
	numerator *= q.numerator;
	denominator *= q.denominator;
	simplify();
	return *this;
}

Rational& Rational::operator/=(Rational const& q)
{
	if (q.numerator == 0)
		throw string("Division par zéro");
	else
	{
		numerator *= q.denominator;
		denominator *= q.numerator;
		simplify();
		return *this;
	}
}

Rational operator+(Rational const& a, Rational const& b)
{
	Rational copie(a);
	copie+= b;
	return copie;
}

Rational operator-(Rational const& a, Rational const& b)
{
	Rational copie(a);
	copie-= b;
	return copie;
}

void Rational::invertSign()
{
    numerator = - numerator;
}

Rational operator-(Rational const& q)
{
    Rational copie(q);
    copie.invertSign();
    return copie;
}

Rational operator*(Rational const& a, Rational const& b)
{
	Rational copie(a);
	copie*= b;
	return copie;
}

Rational operator/(Rational const& a, Rational const& b)
{
	Rational copie(a);
	copie/= b;
	return copie;
}

/**********************\
| Comparison Operators |
\**********************/

bool Rational::equals(Rational const& q) const
{
	return ((numerator == q.numerator) && (denominator == q.denominator));
}

bool Rational::lower(Rational const& q) const
{
	return (numerator * q.denominator < denominator * q.numerator);
}

bool Rational::lowerOrEqual(Rational const& q) const
{
	return (numerator * q.denominator <= denominator * q.numerator);
}

bool operator ==(Rational const& a, Rational const& b)
{
	return (a.equals(b));
}

bool operator !=(Rational const& a, Rational const& b)
{
	return (!(a.equals(b)));
}

bool operator <(Rational const& a, Rational const& b)
{
	return (a.lower(b));
}

bool operator <=(Rational const& a, Rational const& b)
{
	return (a.lowerOrEqual(b));
}

bool operator >(Rational const& a, Rational const& b)
{
	return (!(a.lowerOrEqual(b)));
}

bool operator >=(Rational const& a, Rational const& b)
{
	return (!(a.lower(b)));
}
