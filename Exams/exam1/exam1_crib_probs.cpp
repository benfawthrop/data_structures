//
// Created by Benjamin Fawthrop on 2/1/23.
//


#include <iostream>
#include <vector>
#include <algorithm>

bool compare(int a, int b) {
    return a > b;
}
int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::sort(numbers.begin(), numbers.end(), compare);
    return 0;
}


#include <iostream>
#include <cstdlib>

int main() {
    int*** first = new int**;
    *first = new int*;
    **first = new int;
    ***first = 1;

    return 0;
}

int* z;
int q[3] = { 1, 2, 3 };
z = &q[1];
std::string* y = new std::string[2];
y[0] = "ox";
y[1] = "cat";
y = new std::string;
*y = "five";
int* x;
int p = 20;
x = &p;

