//
// Created by Benjamin Fawthrop on 1/25/23.
//
#include <iostream>

void compute_squares(int *a, int *b, unsigned int n){
    for (int i = 0; i < n; i++){
        *(b + i) = ((*(a + i)) * (*(a + i)));
    }
}

int main(){
    int test1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int test1_out[10];
    compute_squares(test1, test1_out, 10);
    std::cout << "our init array is {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}" << std::endl;
    std::cout << "our output is:" << std::endl << "{";
    for (int i = 0; i < 10; i++){
        std::cout << " " << *(test1_out + i) << " ";
    }
    std::cout << "}" << std::endl;
}