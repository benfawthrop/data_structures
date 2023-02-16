//
// Created by Benjamin Fawthrop on 2/15/23.
//

#include <iostream>
#include <string>
#include <vector>


template <class T>
void print(std::vector<T> &data, const std::string &label) {
    std::cout << label << " ";
    for (unsigned long i = 0; i < data.size(); i++) {
        std::cout << " " << data[i];
    }
    std::cout << std::endl;
}


template <class T>
void reverse(std::vector<T> &data) {
    for (unsigned long i = 0; i < data.size() / 2; i++){
        T temp = data[data.size() - i - 1];
        data[data.size() - i - 1] = data[i];
        data[i] = temp;
    }

}


int main() {
    std::vector<int> data;
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

    std::vector<std::string> data2;
    data2.push_back("apple");
    data2.push_back("banana");
    data2.push_back("carrot");
    data2.push_back("date");

    print(data2,"before:");
    reverse(data2);
    print(data2,"after: ");
}