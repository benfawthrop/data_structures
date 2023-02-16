#include "Matrix.h"
#include <iostream>

int main() {
    Matrix m2(3, 4, 0);
    std::cout << m2 << std::endl;
    double** qwerty = m2.getMatrix();
    std::cout << qwerty[1][1] << std::endl;

    double* val = m2.get_col(2);
    for (unsigned int i = 0; i < 3; i++){
        std::cout << val[i] << " ";
    }
    std::cout << std::endl;
    delete[] val;
    std::cout << m2 << std::endl;



    double val2;
    bool t = m2.get(1,1,val2);
    std::cout << "m2.get() returns: " << val2 << std::endl;
    double** val3 = m2.getMatrix();
    std::cout << val3[1][1] << std::endl;

    double* row = m2.get_row(2);
    for (unsigned int i = 0; i < 4; i++){
        std::cout << row[i] << ' ';
    }
    std::cout << std::endl;
}