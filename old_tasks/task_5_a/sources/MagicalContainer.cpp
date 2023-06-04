#include "MagicalContainer.hpp"

void MagicalContainer::addElement(int element)
{
    // if (currentSize == capacity)
    // {
    //     // If the container is full, increase the capacity
    //     unsigned int newCapacity = (capacity == 0) ? 1 : static_cast<unsigned int>(capacity) * 2;

    //     int *newElements = new int[newCapacity];

    //     // Copy existing elements to the new array
    //     for (int i = 0; i < currentSize; i++)
    //     {
    //         newElements[i] = elements[i];
    //     }

    //     // Deallocate the old array
    //     delete[] elements;

    //     // Update capacity and elements pointer
    //     capacity = newCapacity;
    //     elements = newElements;
    // }

    // if (isPrime(element))
    // {
    //     if (primeCurrentSize == primeCapacity)
    //     {
    //         // If the prime array is full, increase the capacity
    //         unsigned int newPrimeCapacity = (primeCapacity == 0) ? 1 : static_cast<unsigned int>(primeCapacity) * 2;

    //         int *newPrimeElements = new int[newPrimeCapacity];

    //         // Copy existing prime elements to the new array
    //         for (int i = 0; i < primeCurrentSize; i++)
    //         {
    //             newPrimeElements[i] = prime_elements[i];
    //         }

    //         // Deallocate the old prime array
    //         delete[] prime_elements;

    //         // Update prime capacity and prime elements pointer
    //         primeCapacity = newPrimeCapacity;
    //         prime_elements = newPrimeElements;
    //     }

    //     // Add the new prime element to the prime array
    //     prime_elements[primeCurrentSize] = element;
    //     primeCurrentSize++;
    //     std::sort(prime_elements, prime_elements + primeCurrentSize);
    // }

    // // Add the new element to the elements array
    // elements[currentSize] = element;
    // currentSize++;
    // std::sort(elements, elements + currentSize);
}

void MagicalContainer::removeElement(int element)
{
    // int index = -1;

    // // Find the index of the element to remove in the elements array
    // for (int i = 0; i < currentSize; i++)
    // {
    //     if (elements[i] == element)
    //     {
    //         index = i;
    //         break;
    //     }
    // }

    // if (index != -1)
    // {
    //     // If the element is found in the elements array, remove it by shifting elements
    //     for (int i = index; i < currentSize - 1; i++)
    //     {
    //         elements[i] = elements[i + 1];
    //     }

    //     currentSize--;
    // }

    // index = -1;

    // // Find the index of the element to remove in the prime_elements array
    // for (int i = 0; i < primeCurrentSize; i++)
    // {
    //     if (prime_elements[i] == element)
    //     {
    //         index = i;
    //         break;
    //     }
    // }

    // if (index != -1)
    // {
    //     // If the element is found in the prime_elements array, remove it by shifting elements
    //     for (int i = index; i < primeCurrentSize - 1; i++)
    //     {
    //         prime_elements[i] = prime_elements[i + 1];
    //     }

    //     primeCurrentSize--;
    // }
}