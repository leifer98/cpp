#include <vector>
#include <algorithm> // Added for std::sort
#include <cmath>
#include <iostream>

using namespace std;

namespace ariel
{
}

class MagicalContainer
{
private:
    int *elements;              // Dynamic array to store the elements
    int **prime_elements;       // Dynamic array to store the prime indexes
    unsigned int capacity;      // Current capacity of the container
    int currentSize;            // Current number of elements in the container
    unsigned int primeCapacity; // Current capacity of the container
    int primeCurrentSize;       // Current number of elements in the container

public:
    MagicalContainer()
        : elements(nullptr), capacity(0), currentSize(0),
          prime_elements(nullptr), primeCapacity(0), primeCurrentSize(0) {}

    ~MagicalContainer()
    {
    }

    void addElement(int element);

    void removeElement(int element);

    int size() const
    {
        return currentSize;
    }

    int *getPointerSize()
    {
        return &currentSize;
    }

    int **getElements()
    {
        return &elements;
    }

    int ***getPrimeElements()
    {
        return &prime_elements;
    }

    int *getPointerPrimeSize()
    {
        return &primeCurrentSize;
    }

    class AscendingIterator
    {
    private:
        int **pointer_to_elements;
        int *pointer_to_size;
        int index;

    public:
        AscendingIterator(MagicalContainer magicalContainer)
            : pointer_to_elements(magicalContainer.getElements()),
              pointer_to_size(magicalContainer.getPointerSize()), index(0)
        {
        }

        AscendingIterator(const AscendingIterator &other, int index)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(index)
        {
        }

        AscendingIterator(const AscendingIterator &other)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index)
        {
        }

        // Move constructor
        AscendingIterator(AscendingIterator &&other) noexcept
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index)
        {
            other.pointer_to_elements = nullptr;
            other.pointer_to_size = nullptr;
            other.index = 0;
        }

        // Move assignment operator
        AscendingIterator &operator=(AscendingIterator &&other) noexcept
        {
            if (this != &other)
            {
                pointer_to_elements = other.pointer_to_elements;
                pointer_to_size = other.pointer_to_size;
                index = other.index;

                other.pointer_to_elements = nullptr;
                other.pointer_to_size = nullptr;
                other.index = 0;
            }
            return *this;
        }

        ~AscendingIterator() {}

        int &operator*() const
        {
            return (*pointer_to_elements)[index];
        }

        int *operator->() const
        {
            return &(*pointer_to_elements)[index];
        }

        AscendingIterator &operator++()
        {
            if (index == *pointer_to_size)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            ++index;
            return *this;
        }

        AscendingIterator operator++(int)
        {
            if (index == *pointer_to_size)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            AscendingIterator tmp = *this;
            ++index;
            return tmp;
        }

        bool operator==(const AscendingIterator &rhs) const
        {
            return index == rhs.index && *pointer_to_elements == *(rhs.pointer_to_elements);
        }

        bool operator!=(const AscendingIterator &rhs) const
        {
            return !(index == rhs.index);
        }

        AscendingIterator &operator=(const AscendingIterator &other)
        {
            if (this != &other)
            {
                if (this->pointer_to_elements != other.pointer_to_elements)
                {
                    throw runtime_error("iterators are pointing at different containers");
                }
                *this = AscendingIterator{other};
            }
            return *this;
        }

        bool operator>(const AscendingIterator &other) const
        {
            return index > other.index;
        }

        bool operator<(const AscendingIterator &other) const
        {
            return index < other.index;
        }

        AscendingIterator begin()
        {
            return AscendingIterator{*this, 0};
        }

        AscendingIterator end()
        {
            if (*pointer_to_size == 0)
            {
                return AscendingIterator(*this, 0);
            }
            return AscendingIterator{*this, *pointer_to_size};
        }
    };

    class SideCrossIterator
    {
    private:
        int **pointer_to_elements;
        int *pointer_to_size;
        int index;
        bool fromBeginning;

    public:
        SideCrossIterator(MagicalContainer magicalContainer)
            : pointer_to_elements(magicalContainer.getElements()),
              pointer_to_size(magicalContainer.getPointerSize()),
              index(0),
              fromBeginning(true)
        {
        }

        SideCrossIterator(const SideCrossIterator &other)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index),
              fromBeginning(other.fromBeginning)
        {
        }

        SideCrossIterator(const SideCrossIterator &other, int index, bool fromBeginning)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(index),
              fromBeginning(fromBeginning)
        {
        }

        // Move constructor
        SideCrossIterator(SideCrossIterator &&other) noexcept
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index),
              fromBeginning(other.fromBeginning)
        {
            other.pointer_to_elements = nullptr;
            other.pointer_to_size = nullptr;
            other.index = 0;
            other.fromBeginning = true;
        }

        // Move assignment operator
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept
        {
            if (this != &other)
            {
                pointer_to_elements = other.pointer_to_elements;
                pointer_to_size = other.pointer_to_size;
                index = other.index;
                fromBeginning = other.fromBeginning;

                other.pointer_to_elements = nullptr;
                other.pointer_to_size = nullptr;
                other.index = 0;
                other.fromBeginning = true;
            }
            return *this;
        }

        ~SideCrossIterator() {}

        int &operator*() const
        {
            return (*pointer_to_elements)[index];
        }

        int *operator->() const
        {
            return &(*pointer_to_elements)[index];
        }

        SideCrossIterator &operator++()
        {
            if (index == -1)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            if ((int)((*pointer_to_size) / 2) == index)
            {
                index = -1;
                return *this;
            }
            if (fromBeginning)
            {
                index = *pointer_to_size - index - 1;
                fromBeginning = false;
            }
            else
            {
                index = *pointer_to_size - index;
                fromBeginning = true;
            }
            return *this;
        }

        SideCrossIterator operator++(int)
        {
            if (index == -1)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            SideCrossIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const SideCrossIterator &rhs) const
        {
            return index == rhs.index && *pointer_to_elements == *(rhs.pointer_to_elements);
        }

        bool operator!=(const SideCrossIterator &rhs) const
        {
            return !(*this == rhs);
        }

        SideCrossIterator &operator=(const SideCrossIterator &other)
        {
            if (this != &other)
            {
                if (this->pointer_to_elements != other.pointer_to_elements)
                {
                    throw runtime_error("iterators are pointing at different containers");
                }

                *this = SideCrossIterator{other};
            }
            return *this;
        }

        bool operator>(const SideCrossIterator &other) const
        {
            if (index == -1 || other.index == -1)
            {
                throw runtime_error("Comparing with end iterator");
            }

            if (fromBeginning)
            {
                if (other.fromBeginning)
                {
                    return index > other.index;
                }
                int new_index = *pointer_to_size - other.index;
                return index > new_index;
            }
            if (!other.fromBeginning)
            {
                return index < other.index;
            }
            int new_index = *pointer_to_size - index;
            return new_index >= other.index;
        }

        bool operator<(const SideCrossIterator &other) const
        {
            return !(*this > other || *this == other);
        }

        SideCrossIterator begin()
        {
            return SideCrossIterator(*this, 0, true);
        }

        SideCrossIterator end()
        {
            if (*pointer_to_size == 0)
            {
                return SideCrossIterator(*this, 0, true);
            }
            return SideCrossIterator(*this, -1, true);
        }
    };

    class PrimeIterator
    {
    private:
        int ***pointer_to_elements;
        int *pointer_to_size;
        int index;

    public:
        PrimeIterator(MagicalContainer magicalContainer)
            : pointer_to_elements(magicalContainer.getPrimeElements()),
              pointer_to_size(magicalContainer.getPointerPrimeSize()), index(0)
        {
        }

        PrimeIterator(const PrimeIterator &other)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index)
        {
        }

        PrimeIterator(const PrimeIterator &other, int index)
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(index)
        {
        }

        // Move constructor
        PrimeIterator(PrimeIterator &&other) noexcept
            : pointer_to_elements(other.pointer_to_elements),
              pointer_to_size(other.pointer_to_size),
              index(other.index)
        {
            other.pointer_to_elements = nullptr;
            other.pointer_to_size = nullptr;
            other.index = 0;
        }

        // Move assignment operator
        PrimeIterator &operator=(PrimeIterator &&other) noexcept
        {
            if (this != &other)
            {
                pointer_to_elements = other.pointer_to_elements;
                pointer_to_size = other.pointer_to_size;
                index = other.index;

                other.pointer_to_elements = nullptr;
                other.pointer_to_size = nullptr;
                other.index = 0;
            }
            return *this;
        }

        ~PrimeIterator() {}

        int &operator*() const
        {
            return *((*pointer_to_elements)[index]);
        }

        int *operator->() const
        {
            return ((*pointer_to_elements)[index]);
        }

        PrimeIterator &operator++()
        {
            if (index == *pointer_to_size)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            ++index;
            return *this;
        }

        PrimeIterator operator++(int)
        {
            if (index == *pointer_to_size)
            {
                throw runtime_error("Iterator Increment Beyond End");
            }
            PrimeIterator tmp = *this;
            ++index;
            return tmp;
            return *this;
        }

        bool operator==(const PrimeIterator &rhs) const
        {
            return index == rhs.index && *pointer_to_elements == *(rhs.pointer_to_elements);
        }

        bool operator!=(const PrimeIterator &rhs) const
        {
            return !(index == rhs.index);
        }

        PrimeIterator &operator=(const PrimeIterator &other)
        {
            if (this != &other)
            {
                if (this->pointer_to_elements != other.pointer_to_elements)
                {
                    throw runtime_error("iterators are pointing at different containers");
                }
                *this = PrimeIterator{other};
            }
            return *this;
        }

        bool operator>(const PrimeIterator &other) const
        {
            return index > other.index;
        }

        bool operator<(const PrimeIterator &other) const
        {
            return index < other.index;
        }

        PrimeIterator begin()
        {
            return PrimeIterator{*this, 0};
        }

        PrimeIterator end()
        {
            if (*pointer_to_size == 0)
            {
                return PrimeIterator(*this, 0);
            }
            return PrimeIterator{*this, *pointer_to_size};
        }
    };
};