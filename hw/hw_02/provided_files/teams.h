#ifndef __ds_teams__
#define __ds_teams__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "players.h"

class Team {
    public:
        // constructor
        Team(const std::string& _team = "");

        // getters
        int getGoals() const; // returns number of goals
        int getPens() const; // returns number of penalties
        int getWins() const; // returns number of wins
        int getLosses() const; // returns number of losses
        int getTies() const; // returns number of ties
        std::string getTeamName() const; // returns the name of the team
        std::vector<Player> getPlayers(); // returns the vector of player class objects
        double getWinPct() const; // returns the win percentage of the team

        // setters
        void addGoal(int num_goals = 1); // increments the goal counter
        void addPen(int num_pens = 1); // increments the penalty counter
        void addWin(); // increments the win counter
        void addLoss(int num_loss = 1); // increments the loss counter
        void addTie(); // increments the tie counter
        void addPlayer(Player& p); // adds a player class object to the `players` vector

        // misc
        void printTeamStats(int longest_team_name, std::ofstream& outfile); // prints the teams stats according to the parameters on the assignment




    private:
        std::string name;
        std::vector<Player> players;
        int goals;
        int pens;
        int wins;
        int losses;
        int ties;

};

bool operator< (const Team& left, const Team& right); // this is the < operator.  it will be utilized in the sort function
#endif