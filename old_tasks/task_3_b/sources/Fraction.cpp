#include "Fraction.hpp"
#include <limits.h>

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
    Fraction c = Fraction(this->num, this->denum).reduce();
    Fraction o = Fraction(other.num, other.denum).reduce();
    // multiply the numerators and denominators separately
    long long commonDenum = static_cast<long long>(c.denum) * static_cast<long long>(o.denum);
    long long newNum1 = static_cast<long long>(c.num) * static_cast<long long>(o.denum);
    long long newNum2 = static_cast<long long>(c.denum) * static_cast<long long>(o.num);
    long long newNum3 = newNum1 + newNum2;

    // check for overflow
    if (commonDenum > std::numeric_limits<int>::max() || commonDenum < std::numeric_limits<int>::min() ||
        newNum3 > std::numeric_limits<int>::max() || newNum3 < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Fraction multiplication overflow");
    }
    return Fraction(static_cast<int>(newNum3), static_cast<int>(commonDenum)).reduce();
}

Fraction Fraction::operator-(const Fraction &other)
{
    Fraction c = Fraction(this->num, this->denum).reduce();
    Fraction o = Fraction(other.num, other.denum).reduce();
    // multiply the numerators and denominators separately
    long long commonDenum = static_cast<long long>(c.denum) * static_cast<long long>(o.denum);
    long long newNum1 = static_cast<long long>(c.num) * static_cast<long long>(o.denum);
    long long newNum2 = static_cast<long long>(c.denum) * static_cast<long long>(o.num);
    long long newNum3 = newNum1 - newNum2;

    // check for overflow
    if (commonDenum > std::numeric_limits<int>::max() || commonDenum < std::numeric_limits<int>::min() ||
        newNum3 > std::numeric_limits<int>::max() || newNum3 < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Fraction multiplication overflow");
    }
    return Fraction(static_cast<int>(newNum3), static_cast<int>(commonDenum)).reduce();
}

Fraction Fraction::operator*(const Fraction &other)
{
    Fraction c = Fraction(this->num, this->denum).reduce();
    Fraction o = Fraction(other.num, other.denum).reduce();
    // multiply the numerators and denominators separately
    long long newNum = static_cast<long long>(c.num) * static_cast<long long>(o.num);
    long long newDenum = static_cast<long long>(c.denum) * static_cast<long long>(o.denum);

    // check for overflow
    if (newNum > std::numeric_limits<int>::max() || newNum < std::numeric_limits<int>::min() ||
        newDenum > std::numeric_limits<int>::max() || newDenum < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Fraction multiplication overflow");
    }

    // return the result as a new fraction
    return Fraction(static_cast<int>(newNum), static_cast<int>(newDenum)).reduce();
}

Fraction Fraction::operator/(const Fraction &other)
{
    if (other.num == 0)
    {
        throw std::runtime_error("Denominator cannot be zero.");
    }

    Fraction invFraction(other.denum, other.num);
    return ((*this) * invFraction).reduce();
}

Fraction &Fraction::operator++()
{
    // increment the fraction by 1/1
    *this = *this + Fraction(1, 1);
    // return a reference to this fraction
    return *this;
}

Fraction Fraction::operator++(int)
{
    // save the current value of the fraction
    Fraction c = Fraction(this->num, this->denum);
    // increment the fraction by 1/1
    *this = *this + Fraction(1, 1);
    // return the previous value of this fraction
    return c;
}

Fraction &Fraction::operator--()
{
    // decrement the fraction by 1/1
    *this = *this - Fraction(1, 1);
    // return a reference to this fraction
    return *this;
}

Fraction Fraction::operator--(int)
{
    // save the current value of the fraction
    Fraction c = Fraction(this->num, this->denum);
    // decrement the fraction by 1/1
    *this = *this - Fraction(1, 1);
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
    Fraction f1 = other + 0;
    Fraction f2 = *this + 0;
    int newNum1 = f2.num * f1.denum;
    int newNum2 = f1.num * f2.denum;
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
    Fraction f2 = fraction + 0;
    oss << f2.num << "/" << f2.denum;
    return oss;
}

std::istream &operator>>(std::istream &iss, Fraction &fraction)
{
    int num, denom;
    char slash;
    if (iss >> num >> denom)
    {
        if (denom == 0)
        {
            throw std::runtime_error("Invalid input: Denominator cannot be zero");
        }
        else
        {
            fraction = Fraction(num, denom);
        }
    }
    else
    {
        throw std::runtime_error("Invalid input: input must be in the format 'num denom'");
    }
    return iss;
}

Fraction Fraction::reduce()
{
    // reduce the fraction to its simplest form
    int a = this->num;
    int b = this->denum;
    if (a < 0)
    {
        a = -a;
    }
    if (b < 0)
    {
        b = -b;
    }

    if (b < a)
    {
        int temp = b;
        b = a;
        a = temp;
    }
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    this->num /= a;
    this->denum /= a;
    if (this->denum < 0)
    {
        this->denum = -1 * this->denum;
        this->num = -1 * this->num;
    }
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