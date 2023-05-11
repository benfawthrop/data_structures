//
// Created by Benjamin Fawthrop on 3/7/23.
//

#ifndef HW_05_BOARD_H
#define HW_05_BOARD_H
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>


// class that is the basic structure of a word
// search board, with a few helper functions
// all the comments for the function declarations
// are in the Board.cpp file
class Board {
public:
    // constructors
    Board ( int _width = 0, int _height = 0) :
                width(_width), height(_height) { populate(); is_valid = false; }
    Board (const Board &to_copy); // copy constructor


    // getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    bool searchHelper(std::string word, int x, int y);
    bool validate(std::vector<std::string> bad);

    // setters
    std::vector<Board> addRandomLetters(std::vector<std::string> bad_words);
    bool addWord(std::string &word, int x, int y, int direction);

    // outputs
    std::ostream& printBoard(std::ostream &out);


    //operators
    bool operator==(Board &other);
    std::ostream& operator<<(std::ostream &out) { return printBoard(out); }

private:
    int width, height;
    std::vector<std::vector<char> > board;
    bool is_valid;
    bool go_direction(std::string &word, const int &direction, int x, int y, int index);
    bool add_helper(std::string &word, const int &direction, int x, int y, int index);

    void populate();
};

// two main recursive functions for building boards
std::vector<Board> findBoards(std::vector<std::string> &to_use,
                std::vector<std::string> &to_skip, int width, int height);
void boardsHelper(Board &board, std::vector<std::string> &to_use,
                  std::vector<std::string> &to_skip, int width, int height, int x, int y,
                  std::vector<Board> &final_boards);

#endif //HW_05_BOARD_H
