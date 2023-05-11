//
//
// Created by Benjamin Fawthrop on 3/7/23.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// copy constructor
Board::Board(const Board &to_copy) {
    width = to_copy.width;
    height = to_copy.height;
    board = to_copy.board;
    is_valid = to_copy.is_valid;
}

// populates the board private member
void Board::populate() {
    std::vector<char> temp;
    for (int i = 0; i < width; i++) {
        temp.push_back('\0');
    }
    for (int i = 0; i < height; i++) {
        board.push_back(temp);
    }
}

// checks to see if two boards are identical
bool Board::operator==(Board &other) {
    return board == other.board;
}

std::ostream& Board::printBoard(std::ostream &out) {
    // iterates through the whole board vector, and prints it out
    // according to the assignment specs
    out << "Board:" << std::endl;
    for (int i = 0; i < height; i++) {
        out << "  ";
        for (int j = 0; j < width; j++) {
            out << board[i][j];
        }
        out << std::endl;
    }
    return out;
}


// function that checks surrounding letters at a given position
// if the letter occurs at any of the surrounding points, the go_direction (recursive search)
// function is called to search in that direction
bool Board::searchHelper(std::string word, int x, int y) {
    /*
     * For direction;
     * 0 is North
     * 1 is NE
     * 2 is E
     * 3 is SE
     * 4 is S
     * 5 is SW
     * 6 is W
     * 7 is NW
     */
    // stores which directions are possible
    std::vector<int> directions;
    if (y - 1 >= 0 && board[y - 1][x] == word[1]) {
        directions.push_back(0);
    } if ( y - 1 >= 0 && x + 1 < width && board[y-1][x+1] == word[1]) {
        directions.push_back(1);
    } if ( x + 1 < width && board[y][x+1] == word[1]) {
        directions.push_back(2);
    } if ( y + 1 < height && x + 1 < width && board[y+1][x+1] == word[1]) {
        directions.push_back(3);
    } if ( y + 1 < height && board[y+1][x] == word[1]) {
        directions.push_back(4);
    } if ( y + 1 < height && x - 1 >= 0 && board[y+1][x-1] == word[1]) {
        directions.push_back(5);
    } if ( x - 1 >= 0 && board[y][x-1] == word[1]) {
        directions.push_back(6);
    } if ( x - 1 >= 0 && y - 1 >= 0 && board[y-1][x-1] == word[1]) {
        directions.push_back(7);
    }

    for (unsigned long int i = 0; i < directions.size(); i++) {
        // iterates through all possible directions to check if a word is there
        bool exists = go_direction(word, directions[i], x, y, 0);
        if (exists)
            return exists;
    }
    return false;
}

bool Board::validate(std::vector<std::string> bad) {
    // the two arguments must be copy because we need to change them inside the function, but
    // have them remain the same outside

    // iterators for the two vectors
    std::vector<std::string>::iterator bit;
    // iterates through rows
    for (int i = 0; i < height; i++) {
        // iterates through each ele of each row
        for (int j = 0; j < width; j++) {
            // checks for bad words
            for (bit = bad.begin(); bit != bad.end(); ++bit) {
                if ((*bit)[0] == board[i][j]) {
                    // if any of the bad words is ever found, the whole function dies
                    bool bad_exists = searchHelper(*bit, j, i);
                    if (bad_exists) { return false; }
                }
            }
        }
    }
    // if there are any words left that weren't found, return false
    is_valid = true;
    return true;
}

// recursive helper function to the "search" function
bool Board::go_direction(std::string &word, const int &direction, int x, int y, int index) {
    // end cases of the recursion
    if (index == int(word.size())) {
        // if the word is valid
        return true;
    }
    if ( x >= width || x < 0 || y >= height || y < 0 || word[index] != board[y][x]) {
        // if the word isn't valid, or we hit any edge of the board
        return false;
    }
    /*
     * For direction;
     * 0 is North
     * 1 is NE
     * 2 is E
     * 3 is SE
     * 4 is S
     * 5 is SW
     * 6 is W
     * 7 is NW
     */
    // makes sure we continue in the correct direction
    if (direction == 0) {
        return go_direction(word, direction, x, --y, ++index);
    } else if (direction == 1) {
        return go_direction(word, direction, ++x, --y, ++index);
    } else if (direction == 2) {
        return go_direction(word, direction, ++x, y, ++index);
    } else if (direction == 3) {
        return go_direction(word, direction, ++x, ++y, ++index);
    } else if (direction == 4) {
        return go_direction(word, direction, x, ++y, ++index);
    } else if (direction == 5) {
        return go_direction(word, direction, --x, ++y, ++index);
    } else if (direction == 6) {
        return go_direction(word, direction, --x, y, ++index);
    } else if (direction == 7) {
        return go_direction(word, direction, --x, --y, ++index);
    }
    return false;
}

// helper that adds a word recursively
bool Board::add_helper(std::string &word, const int &direction, int x, int y, int index) {
    if (index == int(word.size())) {
        // if the word is valid (we hit the end of the word)
        return true;
    }
    if (x >= width || x < 0 || y >= height || y < 0 || (!(board[y][x] == '\0')
        && board[y][x] != word[index]) ) {
        // if we hit the edge of the board, the function dies
        return false;
    }

    /*
     * For direction;
     * 0 is North
     * 1 is NE
     * 2 is E
     * 3 is SE
     * 4 is S
     * 5 is SW
     * 6 is W
     * 7 is NW
     */
    // makes sure we keep adding in the correct direction
    bool result = true;
    if (direction == 0) {
        result = add_helper(word, direction, x, y-1, index+1);
    } else if (direction == 1) {
        result = add_helper(word, direction, x+1, y-1, index+1);
    } else if (direction == 2) {
        result = add_helper(word, direction, x+1, y, index+1);
    } else if (direction == 3) {
        result = add_helper(word, direction, x+1, y+1, index+1);
    } else if (direction == 4) {
        result = add_helper(word, direction, x, y+1, index+1);
    } else if (direction == 5) {
        result = add_helper(word, direction, x-1, y+1, index+1);
    } else if (direction == 6) {
        result = add_helper(word, direction, x-1, y, index+1);
    } else if (direction == 7) {
        result = add_helper(word, direction, x-1, y-1, index+1);
    }

    if (result) {
        // adds the letter if the word can fit
        board[y][x] = word[index];
    }
    return result;
}

// uses our add_helper to add the word in the correct direction
bool Board::addWord(std::string &word, int x, int y, int direction) {
    bool result = add_helper(word, direction, x, y, 0);
    return result;
}

// main function call for the program
// creates a blueprint blank board of the correct size, then recurses
std::vector<Board> findBoards(std::vector<std::string> &to_use,
                              std::vector<std::string> &to_skip, int width, int height) {

    Board blueprint(width, height); // default blank board
    std::vector<Board> good_boards;  // vec of good boards
    // recursive function call
    boardsHelper(blueprint, to_use, to_skip, width, height, 0, 0, good_boards);
    return good_boards; // returns our vector of boards
}

// creates a vector not including the given word
std::vector<std::string> vec_without(std::vector<std::string> start, std::string &to_remove) {
    std::vector<std::string>::iterator it = start.begin();
    for (; it != start.end(); ++it) {
        if (*it == to_remove) {
            // when we find the correct word, remove it and return
            start.erase(it);
            return start;
        }
    }
    return start; // in case we don't find the word
}

// responsible for filling each board with random letters if it needs them and
// validating boards
std::vector<Board> Board::addRandomLetters(std::vector<std::string> bad_words) {
    std::vector<Board> final_boards; // stores all good boards
    if (!validate(bad_words)) {
        return final_boards; // cuts down on a bunch of useless operations
    }
    // checks al letters
    for (char c = 'a'; c <= 'z'; c++) {
        Board copy(*this); // template copy board
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (copy.board[i][j] == '\0') {
                    copy.board[i][j] = c;
                }
            }
        }
        if (copy.validate(bad_words)) {
            // validates and checks for unique-ness
            bool exists = false;
            for (unsigned long int p = 0; p < final_boards.size(); p++) {
                // makes sure the board is unique
                if (final_boards[p] == copy) {
                    exists = true;
                }
            }
            if (!exists) {
                // adds to the vector
                final_boards.push_back(copy);
            }
        }
    }
    return final_boards;
}



// main recursive function
void boardsHelper(Board &board, std::vector<std::string> &to_use,
                  std::vector<std::string> &to_skip, int width, int height, int x, int y,
                  std::vector<Board> &final_boards) {
    if (to_use.size() == 0) {
        // main base case
        // if all of our words have been used, we check for the bad words
        bool valid = /*board.validate(to_skip);*/ true;
        if (valid) {
            // if there aren't any bad words, we add the word to the vector
            bool exists = false;
            for (unsigned long int p = 0; p < final_boards.size(); p++) {
                // makes sure the board is unique
                if (final_boards[p] == board) {
                    exists = true;
                }
            }
            if (!exists) {
                // adds to the vector
                final_boards.push_back(board);
            }
        }
        return;
    }
    if (y == height && to_use.size() > 0) {
        // base case where not all words can be added
        return;
    }

    // iterates through all words
    for (unsigned long int j = 0; j < to_use.size(); j++) {
        // iterates through all directions
        for (int i = 0; i < 8; i++) {
            // creates a copy of the board, then tries to add the word
            Board copy(board);
            bool can = copy.addWord(to_use[j], x, y, i);

            if (can) {
                // if the word was added, we recurse using a vector of
                // words not including the one we just added
                std::vector<std::string> temp = vec_without(to_use, to_use[j]);
                boardsHelper(copy, temp, to_skip, width, height, 0, 0, final_boards);
            }
        }
    }

    // if we cannot add any word at the given spot, we move on to the next spot
    if (x < width - 1) {
        // moves left in current row
        boardsHelper(board, to_use, to_skip, width, height, x + 1, y, final_boards);
    } else {
        // moves down a row
        boardsHelper(board, to_use, to_skip, width, height, 0, y + 1, final_boards);
    }

}











