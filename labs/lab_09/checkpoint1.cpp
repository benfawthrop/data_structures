//
// Created by Benjamin Fawthrop on 3/15/23.
//
//
// Created by Benjamin Fawthrop on 3/15/23.
//
#include <iostream>
#include <fstream>
#include <map>
#include <vector>


std::map<int, int> check1(std::ifstream &in) {
    std::map<int, int> freq;
    int curr;
    while (in >> curr) {
        freq[curr]++;
    }
    return freq;
}

int main(int argc, char* argv[]) {
    std::ifstream outfile(argv[1]);

    std::map<int, int> freq = check1(outfile);
    std::vector<int> highest;
    int high = 0;
    for ( std::pair<const int, int>& element : freq ) {
        if (element.second > high) {
            highest.clear();
            high = element.second;
            highest.push_back(element.first);
        } else if (element.second == high) {
            highest.push_back(element.first);
        }
    }

    for (int i = 0; i < highest.size(); i++) {
        std::cout << highest[i] << std::endl;
    }
}