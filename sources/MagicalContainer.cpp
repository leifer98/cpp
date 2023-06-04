#include "MagicalContainer.hpp"

bool isPrime(int number)
{
    if (number <= 1)
    {
        return false; // 1 and negative numbers are not prime
    }

    int sqrtNumber = sqrt(number);
    for (int i = 2; i <= sqrtNumber; i++)
    {
        if (number % i == 0)
        {
            return false; // Number is divisible by i, hence not prime
        }
    }

    return true; // Number is prime
}

void MagicalContainer::addElement(int element)
{
    // Add the new element to the elements array
    if (currentSize == capacity)
    {
        // If the container is full, increase the capacity
        unsigned int newCapacity = (capacity == 0) ? 1 : static_cast<unsigned int>(capacity) * 2;

        int *newElements = new int[newCapacity];

        // Copy existing elements to the new array
        for (int i = 0; i < currentSize; i++)
        {
            newElements[i] = elements[i];
        }

        // Deallocate the old array
        delete[] elements;

        // Update capacity and elements pointer
        capacity = newCapacity;
        elements = newElements;
    }

    elements[currentSize] = element;
    currentSize++;
    std::sort(elements, elements + currentSize);

    // Clear and rebuild the prime_elements array
    unsigned int newPrimeCapacity = 0;
    for (int i = 0; i < currentSize; i++)
    {
        if (isPrime(elements[i]))
        {
            newPrimeCapacity++;
        }
    }
    int **newPrimeElements = new int *[newPrimeCapacity];
    primeCurrentSize = 0;
    for (int i = 0; i < currentSize; i++)
    {
        if (isPrime(elements[i]))
        {
            newPrimeElements[primeCurrentSize] = &elements[i];
            primeCurrentSize++;
        }
    }
    primeCapacity = newPrimeCapacity;
    prime_elements = newPrimeElements;
}

void MagicalContainer::removeElement(int element)
{
    int index = -1;

    // Find the index of the element to remove in the elements array
    for (int i = 0; i < currentSize; i++)
    {
        if (elements[i] == element)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        // If the element is found in the elements array, remove it by shifting elements
        for (int i = index; i < currentSize - 1; i++)
        {
            elements[i] = elements[i + 1];
        }

        currentSize--;
    }
    else
    {
        throw runtime_error("Removing a non-existing element");
    }

    index = -1;

    // Find the index of the element to remove in the prime_elements array
    for (int i = 0; i < primeCurrentSize; i++)
    {
        if (prime_elements[i] == &element)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        // If the element is found in the prime_elements array, remove it by shifting elements
        for (int i = index; i < primeCurrentSize - 1; i++)
        {
            prime_elements[i] = prime_elements[i + 1];
        }

        primeCurrentSize--;
    }
}