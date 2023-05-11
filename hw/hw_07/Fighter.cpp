//
// Created by Benjamin Fawthrop on 3/19/23.
//

#include "Fighter.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>

// copy constructor
Fighter::Fighter(const Fighter& to_copy) {
    name = to_copy.name;
    move_speeds = to_copy.move_speeds;
    move_to_sort_by = to_copy.move_to_sort_by;
}

int Fighter::getMoveSpeed(const std::string &move) const{
    return move_speeds.at(move);
}

bool Fighter::operator<(const Fighter& other) const {
    //TODO: Write this
    if (move_speeds.at(move_to_sort_by) == other.move_speeds.at(move_to_sort_by)) {
        // tie breaks using Fighter names
        return name < other.name;
    } else
        return move_speeds.at(move_to_sort_by) < other.move_speeds.at(move_to_sort_by);
}

Fighter& Fighter::operator=(const Fighter& other) {
    if (this != &other) {
        name = other.name;
        move_speeds = other.move_speeds;
        move_to_sort_by = other.move_to_sort_by;
    }
    return *this;
}

std::map<std::string, Fighter> getFrameData(std::ifstream& data_file, std::string move_names[7],
        std::map<std::string, std::set<Fighter> > &move_map) {
    // skips the title cards for the columns in the data file
    std::string skip;
    for (int i = 0; i < 8; i++) {
        data_file >> skip;
    }

    std::map<std::string, Fighter> fighters;
    std::string name;
    while (data_file >> name) {
        Fighter temp(name); // creates fighter obj
        for (int i = 0; i < 7; i++) {
            // gets all the move speeds for each move for the Fighter
            int move;
            data_file >> move;
            temp.move_speeds[move_names[i]] = move;
        }
        for (int i = 0; i < 7; i++) {
            // adds each fighter to the <move, Fighter> maps for each given
            // move based on their speed for that move
            Fighter copy(temp); // copys the fighter
            copy.setSortMove(move_names[i]);
            move_map[move_names[i]].insert(copy);
        }
        // adds to <name, fighter> map
        fighters[name] = temp;
    }
    return fighters;
}