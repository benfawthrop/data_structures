//
// Created by Benjamin Fawthrop on 2/15/23.
//

//
// Created by Benjamin Fawthrop on 2/15/23.
//

#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
    std::cout << label << " ";
    typename std::list<T>::iterator it;
    for (it = data.begin(); it != data.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
    // code for reversing a list here
    typename std::list<T>::iterator it1 = data.begin();
    typename std::list<T>::reverse_iterator it2 = data.rbegin();

    for (unsigned long i = 0; i < data.size() / 2; i++) {
        std::swap(*it1, *it2);
        it1++;
        it2++;
    }
}


int main() {
    std::list<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);

    print(data,"before:");
    reverse(data);
    print(data,"after: ");

    std::list<std::string> data2;
    data2.push_back("apple");
    data2.push_back("banana");
    data2.push_back("carrot");
    data2.push_back("date");

    print(data2,"before:");
    reverse(data2);
    print(data2,"after: ");
}