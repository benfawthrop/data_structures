//
// Created by Benjamin Fawthrop on 3/6/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Board.h"

// gets our inputs from the given command line arguments
void get_inputs(std::ifstream &infile, int &width, int &height,
                std::vector<std::string> &words, std::vector<std::string> &not_words) {
    infile >> width >> height;
    std::string type;
    while (infile >> type) {
        if (type == "+") {
            infile >> type;
            words.push_back(type);
        } else if (type == "-") {
            infile >> type;
            not_words.push_back(type);
        } else {
            std::cerr << "your input file is somehow whack" << std::endl;
            return;
        }
    }
}


// takes three command line args
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "not enough arguments given" << std::endl;
        return 1;
    }

    std::ifstream in_file(argv[1]);
    std::ofstream out_file(argv[2]);
    bool all = false;

    // error checking
    if (!in_file) {
        std::cerr << "given input file, " << argv[1] << " is not a valid file" << std::endl;
        return 1;
    }
    if (!out_file) {
        std::cerr << "given output file, " << argv[2] << " is not a valid file" << std::endl;
        return 1;
    }
    std::string type = argv[3];
    if (type == "all_solutions") {
        all = true;
    } else if (type != "one_solution") {
        std::cout << (argv[3]) << std::endl;
        std::cerr << "given third argument, " << argv[3] << " is not a valid input" << std::endl;
        return 1;
    }

    // declaring variables for use in other functions
    int width, height;
    std::vector<std::string> to_use;
    std::vector<std::string> to_avoid;
    get_inputs(in_file, width, height, to_use, to_avoid);
    std::vector<Board> good_boards = findBoards(to_use, to_avoid, width, height);
    std::vector<Board> good_boards_after;

    for (unsigned long int p = 0; p < good_boards.size(); p++) {
        std::vector<Board> good2 = good_boards[p].addRandomLetters(to_avoid);
        for (unsigned long int i = 0; i < good2.size(); i++) {
            good_boards_after.push_back(good2[i]);
        }
    }
    if (all) {
        out_file << good_boards_after.size() << " solution(s)" << std::endl;
        for (unsigned long int p = 0; p < good_boards_after.size(); p++) {
            good_boards_after[p].printBoard(out_file);
        }
    } else {
        good_boards_after[0].printBoard(out_file);
    }

    return 0;
}