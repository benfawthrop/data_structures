
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "teams.h"
#include <fstream>

// constructor
Team::Team(const std::string& _team){
    name = _team;
    goals = 0;
    pens = 0;
    wins = 0;
    losses = 0;
    ties = 0;
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
void Team::addGoal(int num_goals){ // increments the goal counter
    goals += num_goals;
}
void Team::addPen(int num_pens){ // increments the penalty counter
    pens += num_pens;
}
void Team::addWin(){ // increments the win counter
    wins++;
}
void Team::addLoss(int num_loss){ // increments the loss counter
    losses += num_loss;
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
    outfile << name << std::setw(longest_team_name - name.size() + 4) << wins;
    outfile << std::setw(4) << losses << std::setw(4);
    outfile << ties << std::setw(7) << std::setprecision(2) << std::fixed << getWinPct();
    outfile << std::setw(7) << goals << std::setw(11);
    outfile << pens << std::endl;
}

// this is the < operator.  it will be utilized in the sort function
bool operator< (const Team& left, const Team& right) {
    if ((left.getWinPct()) > (right.getWinPct())){
        return true;
    } else if ((left.getWinPct()) == (right.getWinPct())){
        if (left.getGoals() == right.getGoals()) {
            return (left.getTeamName() < right.getTeamName());
        }
        return (left.getGoals() > right.getGoals());
    } else{
        return false;
    }
}