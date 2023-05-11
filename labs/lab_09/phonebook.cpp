// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, std::string> &phonebook, int number, string const& name) {
    phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(map<int, std::string> & phonebook, int number) {
    if (phonebook.find(number) != phonebook.end())
        cout << phonebook[number] << " is calling!" << endl;
    else
        cout << "unknown caller!" << endl;
}


int main() {
    // create the phonebook; initially all numbers are unassigned
    map<int, std::string> phonebook;

    // add several names to the phonebook
    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");

    // test the phonebook
    identify(phonebook, 2222);
    identify(phonebook, 4444);

    /*
     * TIME COMPLEXITIES:
     *
     * BEFORE CHANGES
     * creating the vector;
     *      O(N), because you are iterating through N numbers in order to allocate the space
     * add;
     *      0(1), because it is just indexing, which is a const time operation
     * identify;
     *      0(1), because it is just indexing, which is a const time operation
     *
     * AFTER
     * creating map;
     *      0(1)
     * add
     *      0(log n)
     * identify
     *      0(log n)
     */
}