
#include <iostream>
#include <cmath>

using namespace std;

namespace ariel
{

}

class Fraction
{
public:
    Fraction(int num, int denum);
    explicit Fraction(double);
    Fraction();

    Fraction operator+(const Fraction& other);
    Fraction operator-(const Fraction& other);
    Fraction operator*(const Fraction& other);
    Fraction operator/(const Fraction& other);

    Fraction &operator++();
    Fraction operator++(int);
    Fraction &operator--();
    Fraction operator--(int);

    bool operator==(const Fraction &other) const;
    bool operator!=(const Fraction &other) const;
    bool operator<(const Fraction &other) const;
    bool operator<=(const Fraction &other) const;
    bool operator>(const Fraction &other) const;
    bool operator>=(const Fraction &other) const;

    friend Fraction operator+(float scalar, const Fraction &fraction);
    friend Fraction operator+(const Fraction &fraction, float scalar);
    friend Fraction operator-(float scalar, const Fraction &fraction);
    friend Fraction operator-(const Fraction &fraction, float scalar);
    friend Fraction operator*(float scalar, const Fraction &fraction);
    friend Fraction operator*(const Fraction &fraction, float scalar);
    friend Fraction operator/(float scalar, const Fraction &fraction);
    friend Fraction operator/(const Fraction &fraction, float scalar);

    friend bool operator==(float scalar, const Fraction &fraction);
    friend bool operator==(const Fraction &fraction, float scalar);
    friend bool operator!=(float scalar, const Fraction &fraction);
    friend bool operator!=(const Fraction &fraction, float scalar);
    friend bool operator>(float scalar, const Fraction &fraction);
    friend bool operator>(const Fraction &fraction, float scalar);
    friend bool operator<(float scalar, const Fraction &fraction);
    friend bool operator<(const Fraction &fraction, float scalar);
    friend bool operator<=(float scalar, const Fraction &fraction);
    friend bool operator<=(const Fraction &fraction, float scalar);
    friend bool operator>=(float scalar, const Fraction &fraction);
    friend bool operator>=(const Fraction &fraction, float scalar);

    friend std::ostream &operator<<(std::ostream &oss, const Fraction &fraction);
    friend std::istream &operator>>(std::istream &iss, Fraction &fraction);

    int getNumerator() const;
    void setNumerator(int num);
    int getDenominator() const;
    void setDenominator(int denum);

private:
    int num;
    int denum;

    Fraction reduce();
};