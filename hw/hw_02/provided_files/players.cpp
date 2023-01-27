
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "players.h"
#include <fstream>


// constructors
Player::Player(const std::string _name, const std::string _team) {
    name = _name;
    team = _team;
    goals = 0;
    assists = 0;
    num_pens = 0;
}

// getters
std::string Player::getName() const{ // returns player name
    return name;
}
std::string Player::getTeam() const{ // returns team name
    return team;
} 
int Player::getGoals() const{ // returns number of goals scored by player
    return goals;
} 
int Player::getAssists() const{ // returns number of assists by player
    return assists;
} 
int Player::getPens() const{ // returns number of pens committed by player
    return num_pens;
} 
std::vector<std::string> Player::getPenaltyVector() const{ 
    // returns a vector of all the pens committed by a player as strings
    return penalties;
} 

// setters
void Player::addGoal(){ // increments our goal counter
    goals++;
}
void Player::addAssist(){ // increments our assists counter
    assists++;
}
void Player::addPen(std::string penalty_name){
    // increments our penalties counter and adds the penalty to the vector of players pens
    num_pens++;
    penalties.push_back(penalty_name);
}

// misc
void Player::printPlayer(int longest_player_name, int longest_team_name, std::ofstream& outfile){
    // prints player stats on a line according to the formatting provided in the document
    outfile << name << std::setw((longest_player_name - name.size()) + 2 + team.size()) << team;
    outfile << std::setw((longest_team_name - team.size()) + 8) << goals << std::setw(9);
    outfile << assists << std::setw(11) << num_pens << std::endl;

}

bool operator< (const Player& left, const Player& right){
    // this is the < operator.  it will be utilized in the sort function
    if ((left.getGoals() + left.getAssists()) > (right.getGoals() + right.getAssists())){
        return true;
    } else if ((left.getGoals() + left.getAssists()) == (right.getGoals() + right.getAssists())){
        if (left.getPens() == right.getPens()) {
            return (left.getName() < right.getName());
        }
        return (left.getPens() < right.getPens());
    } else{
        return false;
    }

}