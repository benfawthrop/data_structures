
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "teams.h"
#include <fstream>

// constructor
Team::Team(const std::string _team){
    name = _team;
}

// getters
int Team::getGoals() const{ // returns number of goals
    return goals;
}
int Team::getPens() const{ // returns number of penalties
    return pens;
}
int Team::getWins() const{ // returns number of wins
    return wins;
}
int Team::getLosses() const{ // returns number of losses
    return losses;
}
int Team::getTies() const{ // returns number of ties
    return ties;
}
std::string Team::getTeamName() const{ // returns the name of the team
    return name;
}
std::vector<Player> Team::getPlayers(){ // returns the vector of player class objects
    return players;
}
double Team::getWinPct() const{ // returns the win percentage of the team
    return double((wins + .5 * ties)/ (wins + losses + ties));
}

// setters
void Team::addGoal(){ // increments the goal counter
    goals++;
}
void Team::addPen(){ // increments the penalty counter
    pens++;
}
void Team::addWin(){ // increments the win counter
    wins++;
}
void Team::addLoss(){ // increments the loss counter
    losses++;
}
void Team::addTie(){ // increments the tie counter
    ties++;
}
void Team::addPlayer(Player& p){ // adds a player class object to the `players` vector
    players.push_back(p);
}

// misc
void Team::printTeamStats(int longest_team_name, std::ofstream& outfile){
    // prints the teams stats according to the parameters on the assignment
    outfile << name << std::setw(longest_team_name + 5) << goals;
    outfile << std::setw(longest_team_name + 5 + 4) << losses << std::setw(longest_team_name + 5 + 4 + 4);
    outfile << ties << std::setw(longest_team_name + 13 + 7) << std::setprecision(3) << getWinPct();
    outfile << std::setw(longest_team_name + 13 + 14) << goals << std::setw(longest_team_name + 27 + 11);
    outfile << pens << std::endl;
}