#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;

MagicalContainer create()
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    return container;
}

TEST_CASE("Object Initialization")
{
    SUBCASE("Initializing MagicalContainer")
    {
        CHECK_NOTHROW(MagicalContainer container);
    }

    SUBCASE("Initializing AscendingIterator with an empty container")
    {
        MagicalContainer container;
        // CHECK_THROWS_AS(MagicalContainer::AscendingIterator ascIter(container), std::runtime_error);
    }

    SUBCASE("Initializing AscendingIterator with a non-empty container")
    {
        MagicalContainer container;
        container.addElement(10);
        container.addElement(20);
        MagicalContainer::AscendingIterator ascIter(container);
        CHECK_NOTHROW(ascIter.begin());
        CHECK_NOTHROW(ascIter.end());
    }

    SUBCASE("Initializing SideCrossIterator with an empty container")
    {
        MagicalContainer container;
        // CHECK_THROWS_AS(MagicalContainer::SideCrossIterator crossIter(container), std::runtime_error);
    }

    SUBCASE("Initializing SideCrossIterator with a non-empty container")
    {
        MagicalContainer container;
        container.addElement(10);
        container.addElement(20);
        MagicalContainer::SideCrossIterator crossIter(container);
        CHECK_NOTHROW(crossIter.begin());
        CHECK_NOTHROW(crossIter.end());
    }

    SUBCASE("Initializing PrimeIterator with an empty container")
    {
        MagicalContainer container;
        // CHECK_THROWS_AS(MagicalContainer::PrimeIterator primeIter(container), std::runtime_error);
    }

    SUBCASE("Initializing PrimeIterator with a non-empty container")
    {
        MagicalContainer container;
        container.addElement(10);
        container.addElement(20);
        MagicalContainer::PrimeIterator primeIter(container);
        CHECK_NOTHROW(primeIter.begin());
        CHECK_NOTHROW(primeIter.end());
    }
}

TEST_CASE("Adding elements")
{
    MagicalContainer container;

    SUBCASE("single element")
    {
        container.addElement(10);
        CHECK(container.size() == 1);
    }

    SUBCASE("multiple elements")
    {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);
    }

    SUBCASE("duplicate elements")
    {
        container.addElement(10);
        // CHECK_THROWS(container.addElement(10));
    }

    SUBCASE("negative elements")
    {
        container.addElement(-10);
        container.addElement(-20);
        CHECK(container.size() == 2);
    }
}

TEST_CASE("Removing elements")
{

    SUBCASE("single element")
    {
        MagicalContainer container;
        container.addElement(10);
        container.removeElement(10);
        CHECK(container.size() == 0);
    }

    SUBCASE("multiple elements")
    {
        MagicalContainer container;

        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        container.removeElement(20);
        CHECK(container.size() == 2);
    }

    SUBCASE("non-existing element")
    {
        MagicalContainer container;
        container.addElement(10);
        // CHECK_THROWS(container.removeElement(20));
    }

    // SUBCASE("duplicate elements")
    // {
    //     MagicalContainer container;
    //     container.addElement(10);
    //     container.addElement(10);
    //     container.removeElement(10);
    //     CHECK(container.size() == 1);
    // }

    SUBCASE("empty container")
    {
        MagicalContainer container;
        // CHECK_THROWS(container.removeElement(10));
    }
}

TEST_CASE("Adding and Removing a Large Number of Elements")
{

    // Add 1000 elements
    SUBCASE("Adding and Removing elements")
    {
        MagicalContainer container;
        for (int i = 0; i < 1000; ++i)
        {
            container.addElement(i);
            CHECK(container.size() == (i + 1));
        }

        for (int i = 0; i < 500; ++i)
        {
            container.removeElement(i);
            CHECK(container.size() == (1000 - i - 1));
        }
    }
}

TEST_CASE("AscendingIterator - operator*")
{
    SUBCASE("Dereference operator returns the correct value")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("AscendingIterator - operator->")
{

    SUBCASE("Arrow operator returns the correct pointer")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        CHECK(it.operator->() == &(*it));
        ++it;
        CHECK(it.operator->() == &(*it));
    }
}

TEST_CASE("AscendingIterator - copy constructor")
{

    SUBCASE("Copied iterator points to the same elements")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        MagicalContainer::AscendingIterator copiedIter(it);
        CHECK(*it == *copiedIter);
        CHECK(it.operator->() == copiedIter.operator->());
    }

    // SUBCASE("Copied iterator has a separate index")
    // {
    //     // MagicalContainer container = create();
    //     // MagicalContainer::AscendingIterator ascIter(container);
    //     // auto it = ascIter.begin();
    //     // ++it;
    //     // MagicalContainer::AscendingIterator copiedIter(it);
    //     // CHECK(*it == *copiedIter);
    //     // CHECK(it.operator->() == copiedIter.operator->());
    // }
}

TEST_CASE("AscendingIterator - custom constructor")
{

    SUBCASE("Iterator points to the specified index")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        int index = 2; // Points to element 9
        MagicalContainer::AscendingIterator customIter(ascIter, index);
        CHECK(*customIter == 9);
    }
}

TEST_CASE("AscendingIterator - operator++ (prefix)")
{

    SUBCASE("Prefix increment advances the iterator")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 9);
    }
}

TEST_CASE("AscendingIterator - operator++ (postfix)")
{

    // SUBCASE("Postfix increment advances the iterator and returns the previous value")
    // {
    //     MagicalContainer container = create();
    //     MagicalContainer::AscendingIterator ascIter(container);
    //     auto it = ascIter.begin();
    //     CHECK(*it++ == 2);
    //     CHECK(*it++ == 3);
    //     CHECK(*it++ == 9);
    // }
}

TEST_CASE("AscendingIterator - operator==")
{

    SUBCASE("Equality operator returns true for the same index")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter1(container);
        MagicalContainer::AscendingIterator ascIter2(container);
        CHECK(ascIter1 == ascIter2);
        ++ascIter1;
        CHECK(!(ascIter1 == ascIter2));
    }
}

TEST_CASE("AscendingIterator - operator!=")
{

    SUBCASE("Inequality operator returns true for different indices")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter1(container);
        MagicalContainer::AscendingIterator ascIter2(container);
        CHECK(!(ascIter1 != ascIter2));
        ++ascIter1;
        CHECK(ascIter1 != ascIter2);
    }
}

TEST_CASE("AscendingIterator - operator=")
{

    SUBCASE("Assignment operator copies the iterator correctly")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter1(container);
        auto it1 = ascIter1.begin();
        MagicalContainer::AscendingIterator ascIter2(container);
        auto it2 = ascIter2.begin();
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
        ++it1;
        CHECK(*it1 != *it2);
        CHECK(it1.operator->() != it2.operator->());
        it2 = it1;
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
    }
}

TEST_CASE("AscendingIterator - operator>")
{

    SUBCASE("Greater than operator returns true for a greater index")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter1(container);
        MagicalContainer::AscendingIterator ascIter2(container);
        CHECK(!(ascIter1 > ascIter2));
        ++ascIter1;
        CHECK(ascIter1 > ascIter2);
    }
}

TEST_CASE("AscendingIterator - operator<")
{
    SUBCASE("Less than operator returns true for a lesser index")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter1(container);
        MagicalContainer::AscendingIterator ascIter2(container);
        CHECK(!(ascIter1 < ascIter2));
        ++ascIter2;
        CHECK(ascIter1 < ascIter2);
    }
}

TEST_CASE("AscendingIterator - begin()")
{
    SUBCASE("begin() returns an iterator pointing to the first element")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.begin();
        CHECK(*it == 2);
    }
}

TEST_CASE("AscendingIterator - end()")
{
    SUBCASE("end() returns an iterator pointing one past the last element")
    {
        MagicalContainer container = create();
        MagicalContainer::AscendingIterator ascIter(container);
        auto it = ascIter.end();
        CHECK(*it == 25); // Points to the element after the last one
    }
}

TEST_CASE("PrimeIterator - operator*")
{
    SUBCASE("Dereference operator returns the correct prime number")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("PrimeIterator - operator->")
{
    SUBCASE("Arrow operator returns the pointer to the prime number")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        CHECK(it.operator->() == &(*it));
        ++it;
        CHECK(it.operator->() == &(*it));
    }
}

TEST_CASE("PrimeIterator - copy constructor")
{
    SUBCASE("Copied iterator points to the same prime numbers")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        MagicalContainer::PrimeIterator copiedIter(it);
        CHECK(*it == *copiedIter);
        CHECK(it.operator->() == copiedIter.operator->());
    }

    // SUBCASE("Copied iterator has a separate index")
    // {
    //     MagicalContainer container = create();
    //     MagicalContainer::PrimeIterator primeIter(container);
    //     auto it = primeIter.begin();
    //     ++it;
    //     MagicalContainer::PrimeIterator copiedIter(it);
    //     CHECK(*it == *copiedIter);
    //     CHECK(it.operator->() == copiedIter.operator->());
    // }
}

TEST_CASE("PrimeIterator - custom constructor")
{
    SUBCASE("Iterator points to the specified prime index")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        int index = 2; // Points to the second prime number, 3
        MagicalContainer::PrimeIterator customIter(primeIter, index);
        CHECK(*customIter == 3);
    }
}

TEST_CASE("PrimeIterator - operator++ (prefix)")
{
    SUBCASE("Prefix increment advances the iterator to the next prime number")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 17);
    }
}

TEST_CASE("PrimeIterator - operator++ (postfix)")
{
    // SUBCASE("Postfix increment advances the iterator to the next prime number and returns the previous value")
    // {
    //     MagicalContainer container = create();
    //     MagicalContainer::PrimeIterator primeIter(container);
    //     auto it = primeIter.begin();
    //     CHECK(*it++ == 2);
    //     CHECK(*it++ == 3);
    //     CHECK(*it++ == 17);
    // }
}

TEST_CASE("PrimeIterator - operator==")
{
    SUBCASE("Equality operator returns true for the same prime index")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter1(container);
        MagicalContainer::PrimeIterator primeIter2(container);
        CHECK(primeIter1 == primeIter2);
        ++primeIter1;
        CHECK(!(primeIter1 == primeIter2));
    }
}

TEST_CASE("PrimeIterator - operator!=")
{
    SUBCASE("Inequality operator returns true for different prime indices")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter1(container);
        MagicalContainer::PrimeIterator primeIter2(container);
        CHECK(!(primeIter1 != primeIter2));
        ++primeIter1;
        CHECK(primeIter1 != primeIter2);
    }
}

TEST_CASE("PrimeIterator - operator=")
{
    SUBCASE("Assignment operator copies the iterator correctly")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter1(container);
        auto it1 = primeIter1.begin();
        MagicalContainer::PrimeIterator primeIter2(container);
        auto it2 = primeIter2.begin();
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
        ++it1;
        CHECK(*it1 != *it2);
        CHECK(it1.operator->() != it2.operator->());
        it2 = it1;
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
    }
}

TEST_CASE("PrimeIterator - begin()")
{
    SUBCASE("begin() returns an iterator pointing to the first prime number")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.begin();
        CHECK(*it == 2);
    }
}

TEST_CASE("PrimeIterator - end()")
{
    SUBCASE("end() returns an iterator pointing one past the last prime number")
    {
        MagicalContainer container = create();
        MagicalContainer::PrimeIterator primeIter(container);
        auto it = primeIter.end();
        CHECK(*it == 17); // Points to the element after the last prime number
    }
}

TEST_CASE("SideCrossIterator - operator*")
{
    SUBCASE("Dereference operator returns the correct element")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 25);
    }
}

TEST_CASE("SideCrossIterator - operator->")
{
    SUBCASE("Arrow operator returns the pointer to the element")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        CHECK(it.operator->() == &(*it));
        ++it;
        CHECK(it.operator->() == &(*it));
    }
}

TEST_CASE("SideCrossIterator - copy constructor")
{
    SUBCASE("Copied iterator points to the same elements")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        MagicalContainer::SideCrossIterator copiedIter(it);
        CHECK(*it == *copiedIter);
        CHECK(it.operator->() == copiedIter.operator->());
    }

    // SUBCASE("Copied iterator has a separate index")
    // {
    //     MagicalContainer container = create();
    //     MagicalContainer::SideCrossIterator crossIter(container);
    //     auto it = crossIter.begin();
    //     ++it;
    //     MagicalContainer::SideCrossIterator copiedIter(it);
    //     CHECK(*it == *copiedIter);
    //     CHECK(it.operator->() == copiedIter.operator->());
    // }
}

TEST_CASE("SideCrossIterator - custom constructor")
{
    SUBCASE("Iterator points to the specified index")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        int index = 2; // Points to the third element, 25
        MagicalContainer::SideCrossIterator customIter(crossIter, index);
        CHECK(*customIter == 25);
    }
}

TEST_CASE("SideCrossIterator - operator++ (prefix)")
{
    SUBCASE("Prefix increment advances the iterator")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("SideCrossIterator - operator++ (postfix)")
{
    // SUBCASE("Postfix increment advances the iterator and returns the previous value")
    // {
    //     MagicalContainer container = create();
    //     MagicalContainer::SideCrossIterator crossIter(container);
    //     auto it = crossIter.begin();
    //     CHECK(*it++ == 2);
    //     CHECK(*it++ == 25);
    //     CHECK(*it++ == 3);
    // }
}

TEST_CASE("SideCrossIterator - operator==")
{
    SUBCASE("Equality operator returns true for the same index")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter1(container);
        MagicalContainer::SideCrossIterator crossIter2(container);
        CHECK(crossIter1 == crossIter2);
        ++crossIter1;
        CHECK(!(crossIter1 == crossIter2));
    }
}

TEST_CASE("SideCrossIterator - operator!=")
{
    SUBCASE("Inequality operator returns true for different indices")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter1(container);
        MagicalContainer::SideCrossIterator crossIter2(container);
        CHECK(!(crossIter1 != crossIter2));
        ++crossIter1;
        CHECK(crossIter1 != crossIter2);
    }
}

TEST_CASE("SideCrossIterator - operator=")
{
    SUBCASE("Assignment operator copies the iterator correctly")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter1(container);
        auto it1 = crossIter1.begin();
        MagicalContainer::SideCrossIterator crossIter2(container);
        auto it2 = crossIter2.begin();
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
        ++it1;
        CHECK(*it1 != *it2);
        CHECK(it1.operator->() != it2.operator->());
        it2 = it1;
        CHECK(*it1 == *it2);
        CHECK(it1.operator->() == it2.operator->());
    }
}

TEST_CASE("SideCrossIterator - begin()")
{
    SUBCASE("begin() returns an iterator pointing to the first element in cross order")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.begin();
        CHECK(*it == 2);
    }
}

TEST_CASE("SideCrossIterator - end()")
{
    SUBCASE("end() returns an iterator pointing one past the last element in cross order")
    {
        MagicalContainer container = create();
        MagicalContainer::SideCrossIterator crossIter(container);
        auto it = crossIter.end();
        CHECK(*it == 9); // Points to the element after the last one in cross order
    }
}
