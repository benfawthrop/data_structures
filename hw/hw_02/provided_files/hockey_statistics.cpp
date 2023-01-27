/*
Ben Fawthrop
Data structures 
HW 2, Hockey Classes
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "players.h"
#include "teams.h"
#include <algorithm>



// creates a unique team object, and adds wins, losses, and ties
void add_team(std::vector<Team>& t_vector, std::string& team_name, bool win = false, bool lose = false){
    bool exists = false; // stores if the team exists yet

    for (unsigned int i = 0; i < t_vector.size(); i++){
        if (t_vector[i].getTeamName() == team_name){
            if (win){
                t_vector[i].addWin();
            } else if (lose){
                t_vector[i].addLoss();
            } else{
                t_vector[i].addTie();
            }
        }
    }
    if (!exists){ // makes a new team if it doesn't exist yet
        Team t(team_name);
        if (win){
            t.addWin();
        } else if (lose){
            t.addLoss();
        } else{
            t.addTie();
        }

    }
}


// This function is responsible for taking the input from the given file
int read_input(std::ifstream& in_file, std::vector<Player>& player_vector, std::vector<Team>& team_vector){
    std::string curr_word; // stores our current word
    std::string team_of_line; // stores what team each statistic is related to so that it can be added to the player
    int word_count = 0; // counts the number of words in order to skip the date
    int line_index = 0; // stores which word I am on in the current line
    std::string play_type; // stores what type of play the current line is (goal or penalty)
    int final_countdown = 0; // countdown used to skip words
    unsigned int longest_word = 0;



    while (in_file >> curr_word){ // loops through input file to get players and teams


        if (final_countdown > 0){ // iterates our final countdown if it exists
            final_countdown--;
            continue;
        }
        if (curr_word == "OVERTIME"){ // skips the word `OVERTIME`
            continue;
        }
        word_count++; // these two statements iterate our word count and line index
        line_index++; // to figure out where we are in the line
        if (word_count < 8){ // skips date
            continue;
        } else if (isdigit(curr_word[0]) && curr_word.size() > 1){ // skips first word in each line
            if (line_index != 5){
                // resets our counter variables
                line_index = 1;
                team_of_line.clear();
                play_type.clear();
            }
            continue;

        } else if (line_index > 4 && line_index < 7 && play_type != "goal"){ // skips penalties
            continue;
        }

        if (curr_word == "PERIOD"){ // skips the period
            final_countdown = 1;
            continue;
        }

        if (curr_word == "FINAL"){ // resets everything at the end of each game
            team_of_line.clear();
            play_type.clear();
            word_count = 0;
            std::string team1; // name of our first team (away team)
            std::string team2; // name of our second team (home team)
            int team1_score; // score of away team
            int team2_score; // score of home team
            in_file >> team1 >> team1_score >> team2 >> team2_score;
            // adds our teams and adds their wins
            if (team1_score > team2_score){
                add_team(team_vector, team1, true, false);
                add_team(team_vector, team2, false, true);
            } else if (team2_score > team1_score){
                add_team(team_vector, team2, true, false);
                add_team(team_vector, team1, false, true);
            } else {
                add_team(team_vector, team2, false, false);
                add_team(team_vector, team1, false, false);
            }


        }

        if (line_index == 2){ // grabs team name
            team_of_line = curr_word;
        } else if (line_index == 3){ // grabs type of play (penalty or goal)
            if (curr_word == "at"){
                final_countdown = 1;
                line_index = 1;
            }
            play_type = curr_word;
            bool team_exists = false;
            // adds goals and penalties to our team objects
            if (team_vector.size() > 0){
                for (unsigned int j = 0; j < team_vector.size(); j++){
                    if (team_vector[j].getTeamName() == team_of_line){
                        team_exists = true;
                        if (play_type == "goal"){
                            team_vector[j].addGoal();
                        } else if (play_type == "penalty"){
                            team_vector[j].addPen();
                        }
                    }
                }
            }
            // adds a new team object, then adds goals and penalties to that object
            if (!team_exists){
                Team t(team_of_line);
                if (play_type == "goal"){
                    t.addGoal();
                } else if (play_type == "penalty"){
                    t.addPen();
                }
                team_vector.push_back(t);
            }

        } else if (line_index == 4){ // adds the goal or penalty to the player
            bool dup = false;
            if (curr_word == "BENCH"){ // skips the word `BENCH`
                continue;
            }
            if (curr_word.size() > longest_word){
                longest_word = curr_word.size();
            }
            if (player_vector.size() > 0){ // makes sure our vector isn't empty
                for (unsigned int i = 0; i < player_vector.size(); i++){
                    if (player_vector[i].getName() == curr_word){
                        if (play_type == "goal"){
                            player_vector[i].addGoal();
                        } else if (play_type == "penalty"){
                            player_vector[i].addPen();
                        }
                        dup = true; // tells the following code that the person already exists
                    }
                }
            }
            if (!dup){
                Player p(curr_word, team_of_line); // adds a new player if its unique
                if (play_type == "goal"){
                    p.addGoal();
                } else if (play_type == "penalty"){
                    p.addPen();
                }
                player_vector.push_back(p);
            }

        } else if (line_index > 5 && curr_word != ")" && play_type == "goal"){ // adds assists
            bool dup = false;
            for (unsigned int i = 0; i < player_vector.size(); i++){ // checks to see if a player exists yet
                if (player_vector[i].getName() == curr_word){
                    player_vector[i].addAssist();
                    dup = true;
                }
            }
            if (!dup){
                Player p(curr_word, team_of_line); // adds unique
                p.addAssist();
                player_vector.push_back(p);
            }
        }
    } // returns the longest team name that the function finds to be used later for formatting
    return longest_word;
}

// finds the longest team name for formatting
int get_longest_team_name(std::vector<Team>& t_vector){
    unsigned long longest = 0;
    for (unsigned int t = 0; t < t_vector.size(); t++){
        if (longest < t_vector[t].getTeamName().size()){
            longest = t_vector[t].getTeamName().size();
        }
    }
    return longest;
}

void print_player_stats(std::vector<Player>& p_vector, std::ofstream& outfile, int longest_word, int longest_team){
    // prints out all the players as well as their statistics
    outfile<< "Player Name" << std::setw((longest_word - 11) + 2 + 4) << "Team";
    outfile << std::setw((longest_team - 4) + 8) << "Goals" << std::setw(9);
    outfile << "Assists" << std::setw(11) << "Penalties" << std::endl;
    for (unsigned int l = 0; l < p_vector.size(); l++) {
        p_vector[l].printPlayer(longest_word, longest_team, outfile);
    }
}

void print_team_stats(std::vector<Team>& t_vector, std::ofstream& outfile, int longest_team_name){
    // prints out all teams along with their statistics
    outfile << "Team Name" << std::setw( (longest_team_name - 9) + 4) << "W";
    outfile << std::setw(4) << "L" << std::setw(4);
    outfile << "T" << std::setw(7) << "Win%" << std::setw(7) << "Goals";
    outfile << std::setw(11) << "Penalties" << std::endl;
    for (unsigned int l = 0; l < t_vector.size(); l++) {
        t_vector[l].printTeamStats(longest_team_name, outfile);
    }
}

double custom_stat(std::vector<Player>& p_vector){
    // collects the data for our custom stat
    double avg_utility;
    double total_utility = 0;
    for (unsigned int i = 0; i < p_vector.size(); i++){
        // adds our goals and assists to our utility total
        total_utility += p_vector[i].getGoals();
        total_utility += p_vector[i].getAssists();
    }
    // averages the util then returns that double
    avg_utility = double(total_utility / p_vector.size());
    return avg_utility;
}

// responsible for formatting our custom statistic output
void print_custom_stats(std::vector<Player>& p_vector, std::ofstream& outfile){
    std::string most_useful = p_vector[0].getName();
    std::string least_useful = p_vector.back().getName();
    double avg_util = custom_stat(p_vector);
    outfile << "Custom Stat -->" << std::endl;
    outfile << "Average Scoring Utility of All Players: " << std::setprecision(3);
    outfile << avg_util << " (points per season)" << std::endl << std::endl;
    outfile << "Most Valuable Player: " << most_useful << std::endl;
    outfile << "Least Valuable Player: " << least_useful << std::endl;
}

int main(int argc, char* argv[]){
    // streams for input and output
    std::ifstream input_doc;
    std::ofstream output_doc;
    std::string output_type; // stores what type of stats we need to output

    // vectors that store players and teams
    std::vector<Player> player_vector;
    std::vector<Team> team_vector;

    // gets inputs and error checks them all
    if (argc != 4){
        std::cerr << "Usage:\n " << argv[0] << " infile-games outfile-stats eval_type" << std::endl;
        return 1;
    }
    input_doc.open(argv[1]);
    if (!input_doc){
        std::cerr << "Could not open " << argv[1] << " to read" << std::endl;
        return 1;
    }
    output_doc.open(argv[2]);
    if (!output_doc){
        std::cerr << "Could not open " << argv[2] << " to read" << std::endl;
        return 1;
    }
    output_type = argv[3];
    if (output_type != "--team_stats" && output_type != "--player_stats" && output_type != "--custom_stats"){
        std::cerr << "Invalid type argument, please rerun with --team_stats, --player_stats, or --custom_stats" << std::endl;
        return 1;
    }


    // main code goes here

    // reads inputs and gets longest player name
    int longest_w = read_input(input_doc, player_vector, team_vector);

    // gets longest team name
    int longest_t = get_longest_team_name(team_vector);

    // sorts inputs
    std::sort(player_vector.begin(), player_vector.end());
    std::sort(team_vector.begin(), team_vector.end());
    if (output_type == "--player_stats") { // prints player stats
        print_player_stats(player_vector, output_doc, longest_w, longest_t);
    } else if (output_type == "--team_stats") { // prints out team stats
        print_team_stats(team_vector, output_doc, longest_t);
    } else if (output_type == "--custom_stats") { // prints out custom stats
        print_custom_stats(player_vector, output_doc);
    }
    return 0;
}

