#include "Fraction.hpp"

Fraction::Fraction(int num, int denum)
{
    if (denum == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    this->num = num;
    this->denum = denum;
}

Fraction::Fraction(double scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    this->num = f.num;
    this->denum = f.denum;
}

Fraction::Fraction()
{
    num = 0;
    denum = 1;
}

Fraction Fraction::operator+(const Fraction &other)
{
    // calculate the common denominator
    int commonDenom = denum * other.denum;
    // calculate the new numerator
    int newNum = num * other.denum + other.num * denum;

    // return the sum of two fractions in reduced form
    return Fraction(newNum, commonDenom).reduce();
}

Fraction Fraction::operator-(const Fraction &other)
{
    // find a common denominator
    int commonDenum = this->denum * other.denum;
    // calculate the new numerators based on the common denominator
    int newNum1 = this->num * other.denum;
    int newNum2 = other.num * this->denum;
    // subtract the numerators and return the result as a new fraction
    return Fraction(newNum1 - newNum2, commonDenum).reduce();
}

Fraction Fraction::operator*(const Fraction &other)
{
    // multiply the numerators and denominators separately
    int newNum = this->num * other.num;
    int newDenum = this->denum * other.denum;
    // return the result as a new fraction
    return Fraction(newNum, newDenum).reduce();
}

Fraction Fraction::operator/(const Fraction &other)
{
    if (other.num == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero.");
    }

    Fraction invFraction(other.denum, other.num);
    return ((*this) * invFraction).reduce();
}

Fraction &Fraction::operator++()
{
    // decrement the numerator by the denominator
    this->num += this->denum;
    // simplify the fraction
    Fraction f = this->reduce();
    this->denum = f.denum;
    this->num = f.num;
    // return a reference to this fraction
    return *this;
}

Fraction Fraction::operator++(int)
{
    Fraction c = Fraction(this->num, this->denum);
    // decrement the numerator by the denominator
    this->num += this->denum;
    // simplify the fraction
    Fraction f = this->reduce();
    this->denum = f.denum;
    this->num = f.num;
    // return the previous value of this fraction
    return c;
}

Fraction &Fraction::operator--()
{
    // decrement the numerator by the denominator
    this->num -= this->denum;
    // simplify the fraction
    Fraction f = this->reduce();
    this->denum = f.denum;
    this->num = f.num;
    // return a reference to this fraction
    return *this;
}

Fraction Fraction::operator--(int)
{
    Fraction c = Fraction(this->num, this->denum);
    // decrement the numerator by the denominator
    this->num -= this->denum;
    // simplify the fraction
    Fraction f = this->reduce();
    this->denum = f.denum;
    this->num = f.num;
    // return the previous value of this fraction
    return c;
}

bool Fraction::operator==(const Fraction &other) const
{
    // compare the numerators and denominators
    Fraction f1 = other + 0;
    Fraction f2 = *this + 0;
    return (f1.num == f2.num) && (f1.denum == f2.denum);
}

bool Fraction::operator!=(const Fraction &other) const
{
    // use the negation of the equality operator
    return !((*this) == other);
}

bool Fraction::operator<(const Fraction &other) const
{
    // calculate the new numerators based on the common denominator
    int newNum1 = this->num * other.denum;
    int newNum2 = other.num * this->denum;
    // compare the numerators
    return newNum1 < newNum2;
}

bool Fraction::operator<=(const Fraction &other) const
{
    // use the less than or equal to operator or the equality operator
    return ((*this) < other) || ((*this) == other);
}

bool Fraction::operator>(const Fraction &other) const
{
    // use the negation of the less than or equal to operator
    return !((*this) <= other);
}

bool Fraction::operator>=(const Fraction &other) const
{
    // use the negation of the less than operator
    return !((*this) < other);
}

bool operator==(float scalar, const Fraction &fraction)
{
    return fraction == scalar;
}

bool operator==(const Fraction &fraction, float scalar)
{
    // convert the scalar to a fraction and compare with the given fraction
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    return fraction == f;
}

bool operator!=(float scalar, const Fraction &fraction)
{
    return !(fraction == scalar);
}

bool operator!=(const Fraction &fraction, float scalar)
{
    return !(fraction == scalar);
}

bool operator<(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 > newNum2;
}

bool operator<(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 < newNum2;
}

bool operator>(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 < newNum2;
}

bool operator>(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 > newNum2;
}

bool operator<=(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum2 <= newNum1;
}

bool operator<=(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 <= newNum2;
}

bool operator>=(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum2 >= newNum1;
}

bool operator>=(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    // calculate the new numerators based on the common denominator
    int newNum1 = fraction.num * f.denum;
    int newNum2 = f.num * fraction.denum;
    // compare the numerators
    return newNum1 >= newNum2;
}

Fraction operator+(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c + f);
}

Fraction operator+(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c + f);
}

Fraction operator-(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    return (f - fraction);
}

Fraction operator-(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c - f);
}

Fraction operator*(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c * f);
}

Fraction operator*(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c * f);
}

Fraction operator/(float scalar, const Fraction &fraction)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    return (f / fraction);
}

Fraction operator/(const Fraction &fraction, float scalar)
{
    Fraction f = Fraction((int)(scalar * 1000), 1000);
    Fraction c = Fraction(fraction.num, fraction.denum);
    return (c / f);
}

std::ostream &operator<<(std::ostream &oss, const Fraction &fraction)
{
    // print the fraction to the output stream
    oss << fraction.num << "/" << fraction.denum;
    return oss;
}

std::istream &operator>>(std::istream &iss, Fraction &fraction)
{
    // read a fraction from the input stream
    int num, denum;
    char slash;
    iss >> num >> slash >> denum;
    fraction = Fraction(num, denum);
    return iss;
}

Fraction Fraction::reduce()
{
    // reduce the fraction to its simplest form
    int sign = 1;
    if (num < 0)
    {
        sign *= -1;
        num *= -1;
    }
    if (denum < 0)
    {
        sign *= -1;
        denum *= -1;
    }
    if (num == 0)
    {
        denum = 1;
        return *this;
    }
    int smaller = (num < denum) ? num : denum;
    for (int i = smaller; i > 1; i--)
    {
        if (num % i == 0 && denum % i == 0)
        {
            num /= i;
            denum /= i;
        }
    }
    num *= sign;
    return *this;
}

int Fraction::getNumerator() const
{
    return num;
}

void Fraction::setNumerator(int num)
{
    this->num = num;
}

int Fraction::getDenominator() const
{
    return denum;
}

void Fraction::setDenominator(int denum)
{
    this->denum = denum;
}