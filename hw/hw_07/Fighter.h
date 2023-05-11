//
// Created by Benjamin Fawthrop on 3/19/23.
//

#ifndef HW_07_FIGHTER_H
#define HW_07_FIGHTER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

class Fighter {
public:
    // constructors
    Fighter(std::string _name = "") : name(_name) {}
    Fighter(const Fighter& to_copy); // copy constructor

    // getters

    // returns name string
    std::string getName() const { return name; }
    // returns the move speed of a given move
    int getMoveSpeed(const std::string &move) const;

    // setters

    // sets the sort move
    void setSortMove(const std::string &move) { move_to_sort_by = move; }

    // for map and set binary search trees
    bool operator<(const Fighter& other) const;
    Fighter& operator=(const Fighter& other);


    // key is move name; value is the int frame data
    std::map<std::string, int> move_speeds;
private:
    std::string move_to_sort_by;
    std::string name;
};

// function for reading queries from file
std::map<std::string, Fighter> getFrameData(std::ifstream& data_file, std::string move_names[7],
                                            std::map<std::string, std::set<Fighter> > &move_map);

#endif //HW_07_FIGHTER_H
