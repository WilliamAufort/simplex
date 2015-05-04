#ifndef DEF_RATIONAL
#define DEF_RATIONAL

#include <iostream>

class Rational
{
    public:
        Rational(): numerator(0), denominator(1) {};
        Rational(int _numerator, int _denominator): numerator(_numerator), denominator(_denominator) {simplify();};
        Rational(int n): numerator(n), denominator(1) {};
        ~Rational() {};

        int gcd(int a, int b) __attribute__((const));
        void simplify();

        friend std::ostream& operator<<(std::ostream& flux, Rational const& q);
        friend std::string intToString(int a) __attribute__((const));
        friend void printRationalLaTeX(std::string& latex, Rational const& q, bool inDico);

        Rational& operator+=(Rational const& q);
        Rational& operator-=(Rational const& q);
        Rational& operator/=(Rational const& q);
        Rational& operator*=(Rational const& q);

        friend Rational operator-(Rational const& q);

        friend bool operator ==(Rational const& a, Rational const& b) __attribute__((pure));
        friend bool operator !=(Rational const& a, Rational const& b) __attribute__((pure));
        friend bool operator <(Rational const& a, Rational const& b) __attribute__((pure));
        friend bool operator <=(Rational const& a, Rational const& b) __attribute__((pure));
        friend bool operator >(Rational const& a, Rational const& b) __attribute__((pure));
        friend bool operator >=(Rational const& a, Rational const& b) __attribute__((pure));

    private:
        int numerator;
        int denominator;

        void affiche(std::ostream& flux) const;
        void afficheLaTeX(std::string& latex, bool inDico) const;
        bool equals(Rational const& q) const __attribute__((pure));
        bool lower(Rational const& q) const __attribute__((pure));
        bool lowerOrEqual(Rational const& q) const __attribute__((pure));

        void invertSign();
};

Rational operator+(Rational const& a, Rational const& b);
Rational operator-(Rational const& a, Rational const& b);
Rational operator*(Rational const& a, Rational const& b);
Rational operator/(Rational const& a, Rational const& b);

#endif
