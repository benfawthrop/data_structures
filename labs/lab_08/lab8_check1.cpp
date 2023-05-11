//
// Created by Benjamin Fawthrop on 3/1/23.
//
#include <iostream>

// recursively finds all paths
int findOrigin(int x, int y) {
    if (x == 0 && y == 0) {
        return 1;
    } else if (x == 0) {
        return findOrigin(x, y - 1);
    } else if (y == 0) {
        return findOrigin(x - 1, y);
    } else {
        return findOrigin(x - 1, y) + findOrigin(x, y - 1);
    }
}


int main() {
    std::cout << "x == 0, y == 0" << std::endl << findOrigin(0, 0) << std::endl;
    std::cout << "x == 2, y == 1" << std::endl << findOrigin(2, 1) << std::endl;
    std::cout << "x == 2, y == 2" << std::endl << findOrigin(2, 2) << std::endl;
}