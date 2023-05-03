#include "doctest.h" 
#include "sources/Fraction.hpp"
#include <stdexcept>

#define LIMIT 10

TEST_CASE("check initilization")
{
    CHECK_NOTHROW(Fraction(5, 3));
    CHECK_THROWS(Fraction(5, 0));
    CHECK_THROWS(Fraction(0, 0));
}

TEST_CASE("Comparison operators")
{
    Fraction a(5, 3), b(14, 21), c(5, 3);

    CHECK(a == c);
    CHECK(a != b);
    CHECK(a > b);
    CHECK(b < a);
    CHECK(a >= c);
    CHECK(b <= c);

    Fraction d(6, 2);
    int num = 2;
    double dec = 2.5;

    CHECK(!(d == num));
    CHECK(num != b);
    CHECK(!(b > dec));
    CHECK(c < num);
    CHECK(d >= num);
    CHECK(dec <= b);
}

TEST_CASE("Arithmetic operation tests on Fractions")
{
    Fraction a(5, 3), b(14, 21);

    CHECK((a + (b + a)) == ((a + b) + a));
    CHECK((a - (b - a)) != ((a - b) - a));
    CHECK((a * (b * a)) == ((a * b) * a));
    CHECK((a / (b / a)) != ((a / b) / a));
}

TEST_CASE("increment operator")
{
    Fraction f(1, 2);
    for (int i = 0; i < LIMIT; i++)
    {
        f++;
        int num = (i * 2) + 3;
        CHECK(f == Fraction(num, 2));
    }
}

TEST_CASE("decrement operator")
{
    Fraction f(1, 2);
    for (int i = 0; i < LIMIT; i++)
    {
        f--;
        CHECK(f == Fraction((i * -2) - 1, 2));
    }
}

TEST_CASE("divide by 2 operator")
{
    Fraction f(1, 2);
    for (int i = 0; i < LIMIT; i++)
    {
        f = f / 2;
        int denum = pow(2, i + 2);
        CHECK(f == Fraction(1, denum));
    }
}

TEST_CASE("multiply by 2 operator")
{
    Fraction f(1, 2);
    for (int i = 0; i < LIMIT; i++)
    {
        f = f * 2;
        CHECK(f == Fraction(pow(2, i),1));
    }
}

TEST_CASE("Increment and Decrement Test")
{
    Fraction a(1, 2), b(3, 4), c(5, 6);
    // Pre-increment
    CHECK((++a) == Fraction(3, 2));
    CHECK((++b) == Fraction(7, 4));
    CHECK((++c) == Fraction(11, 6));

    // Post-increment
    CHECK((a++) == Fraction(3, 2));
    CHECK(a == Fraction(5, 2));
    CHECK((b++) == Fraction(7, 4));
    CHECK(b == Fraction(11, 4));
    CHECK((c++) == Fraction(11, 6));
    CHECK(c == Fraction(17, 6));

    // Pre-decrement
    CHECK((--a) == Fraction(3, 2));
    CHECK((--b) == Fraction(7, 4));
    CHECK((--c) == Fraction(11, 6));

    // Post-decrement
    CHECK((a--) == Fraction(3, 2));
    CHECK(a == Fraction(1, 2));
    CHECK((b--) == Fraction(7, 4));
    CHECK(b == Fraction(3, 4));
    CHECK((c--) == Fraction(11, 6));
    CHECK(c == Fraction(5, 6));
}

TEST_CASE("Reduce Test")
{
    Fraction a(4, 8), b(10, 20), c(15, 25);
    // Addition
    CHECK((a + b) == Fraction(1, 1));
    CHECK((b + c) == Fraction(11, 10));
    CHECK((a + c) == Fraction(11, 10));
    // Subtraction
    CHECK((a - b) == Fraction(0, 1));
    CHECK((b - c) == Fraction(-1, 10)); 
    CHECK((a - c) == Fraction(-1, 10)); 

    // Multiplication
    CHECK((a * b) == Fraction(1, 4));
    CHECK((b * c) == Fraction(3,10));
    CHECK((a * c) == Fraction(3, 10));

    // Division
    CHECK((a / b) == Fraction(1, 1));
    CHECK((b / c) == Fraction(5, 6));
    CHECK((a / c) == Fraction(5, 6)); 
}
