#include <iostream>
#include <map>

class MagicalContainer
{
private:
    std::map<int, bool> container; // Internal storage using std::map

public:
    void addElement(int element)
    {
        container[element] = true;
    }

    int size() const
    {
        return container.size();
    }

    // AscendingIterator class
    class AscendingIterator
    {
    private:
        std::map<int, bool>::const_iterator current; // Current iterator position

    public:
        AscendingIterator(const MagicalContainer &magicalContainer) : current(magicalContainer.container.begin()) {}

        std::map<int, bool>::const_iterator begin()
        {
            return current;
        }

        std::map<int, bool>::const_iterator end()
        {
            return current;
        }
    };
};

int main()
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    std::cout << "Size of container: " << container.size() << std::endl;

    std::cout << "Elements in ascending order:\n";
    MagicalContainer::AscendingIterator ascIter(container);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << it->first << ' '; // Access the key of the map iterator
    }
    std::cout << std::endl;

    return 0;
}