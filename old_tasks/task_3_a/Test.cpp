#include "doctest.h" // A testing framework
#include "sources/Fraction.hpp"
#include <stdexcept> // Exception classes

#define LIMIT 30

TEST_CASE("check initilization")
{
    // Check if creating a new player does not throw an exception
    CHECK_NOTHROW(Fraction a(5, 3));
    CHECK_NOTHROW(Fraction a(5, 3), b(14, 21));
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
        CHECK(f == Fraction((i * 2) + 3, 2));
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
    int denum = 2;
    for (int i = 0; i < LIMIT; i++)
    {
        f = f / 2;
        denum = denum * 2;
        Fraction t(1, denum);
        CHECK(f == t);
    }
}

TEST_CASE("multiply by 2 operator")
{
    Fraction f(1, 2);
    for (int i = 0; i < LIMIT; i++)
    {
        f = f * 2;
        CHECK(f == Fraction(pow(2, i), 1));
    }
}

TEST_CASE("Increment and Decrement Test")
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
    CHECK((b * c) == Fraction(3, 10));
    CHECK((a * c) == Fraction(3, 10));

    // Division
    CHECK((a / b) == Fraction(1, 1));
    CHECK((b / c) == Fraction(5, 6));
    CHECK((a / c) == Fraction(5, 6));
}