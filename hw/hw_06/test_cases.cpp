//
// Created by Benjamin Fawthrop on 3/11/23.
//
#include <iostream>
#include "Board.h"
#include <fstream>
#include <string>

int main() {

    std::string ban = "ban";
    Board test(3, 2);
    std::string cat = "cat";
    test.addWord(cat, 0, 0, 2);
    std::string one = "one";
    test.addWord(one, 0, 1, 2);
    test.printBoard(std::cout);
//    std::cout << test << std::endl;
    std::vector<std::string> words;
    words.push_back(cat);
    words.push_back(one);
    std::vector<std::string> bad;
    bad.push_back(ban);
    std::cout << test.validate(bad) << std::endl;

    Board test2(3, 3);
    test2.addWord(cat, 0, 0, 3);
    std::string cab = "cab";
    std::string oat = "oat";
    std::string no = "not";

    test2.addWord(ban, 0, 2, 1);
    test2.addWord(cab, 0, 0, 4);
    test2.addWord(oat, 1, 0, 4);
    test2.addWord(no, 2, 0, 4);
    test2.printBoard(std::cout);
    std::cout << test2.validate(words) << std::endl;
//    test.clear();
//    test2.clear();
}

//
//{
//    {  ,  ,  },
//    {  ,  ,  },
//    {  ,  ,  }
//}
