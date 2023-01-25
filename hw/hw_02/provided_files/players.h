#ifndef __ds_players__
#define __ds_players__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class Player {
    public:
        // constructors
        Player(const std::string _name = "", const std::string _team = "");

        // getters
        std::string getName() const; // returns player name
        std::string getTeam() const; // returns team name
        int getGoals() const; // returns number of goals scored by player
        int getAssists() const; // returns number of assists by player
        int getPens() const; // returns number of pens committed by player
        std::vector<std::string> getPenaltyVector() const; // returns a vector of all the pens committed by a player as strings

        // setters
        void addGoal(); // increments our goal counter
        void addAssist(); // increments our assists counter
        void addPen(std::string penalty_name = "");

        // misc
        void printPlayer(int longest_player_name, std::ofstream& outfile); // prints player stats on a line according to the formatting provided in the document


    private:
        // private member variables
        std::string name; // players name seperated by a '_'
        std::string team; // team name
        int goals; // number of goals
        int assists; // number of asts
        int num_pens; // number of penalties
        std::vector<std::string> penalties; // vector of penalties committed

};

bool operator< (const Player& left, const Player& right); // this is the < operator.  it will be utilized in the sort function
#endif