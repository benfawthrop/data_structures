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

std::ifstream input_doc;
std::ofstream output_doc;
std::string output_type;

//global variables
std::vector<Player> player_vector;
std::vector<Team> team_vector;


// This function is responsible for taking the input from the given file
void read_input(std::ifstream& in_file){
    // TODO: make it so that it doesn't grab duplicate names
    std::string curr_word; // stores our current word
    std::string team_of_line; // stores what team each statistic is related to so that it can be added to the player
    int word_count = 0; // counts the number of words in order to skip the date
    bool skip = false; // bool value for if we should skip or not
    int line_index = 0; // stores which word I am on in the current line
    std::string play_type;
    int final_countdown = 0;


    while (in_file >> curr_word){
        if (final_countdown > 0){ // iterates our final countdown if it exists
            final_countdown--;
            continue;
        }
        word_count++; // these two statements iterate our word count and line index
        line_index++; // to figure out where we are in the stats

        if (word_count < 5){ // skips date
            continue;
        } else if (isdigit(curr_word[0]) && curr_word.size() > 1){ // skips first word in each line
            if (line_index != 5){
                line_index = 1;
                team_of_line.clear();
                play_type.clear();
            }
            continue;

        } else if (line_index > 4 && play_type != "goal"){ // skips penalties
            continue;
        }

        if (curr_word == "PERIOD"){ // skips the period
            final_countdown = 1;
            continue;
        }

        if (curr_word == "FINAL"){ // resets everything at the end of each game
            final_countdown = 4;
            team_of_line.clear();
            skip = false;
            play_type.clear();
        }

        if (line_index == 2){ // grabs team name
            team_of_line = curr_word;
        } else if (line_index == 3){ // grabs type of play (penalty or goal)
            play_type = curr_word;
        } else if (line_index == 4){ // adds the goal or penalty to the player
            if (player_vector.size() > 0){ // makes sure our vector isn't empty
                for (unsigned int i = 0; i < player_vector.size(); i++){
                    if (player_vector[i].getName() == curr_word){
                        if (play_type == "goal"){
                            player_vector[i].addGoal();
                        } else if (play_type == "penalty"){
                            player_vector[i].addPen();
                        } else {
                            std::cout << "Your play type is not supported. Here's the broken word: " << play_type << std::endl;
                        }
                        continue; //THIS IS WHERE YOUR DUPLICATION ERROR IS
                    }
                }
            }
            Player p(curr_word, team_of_line); // adds a new player if its unique
            if (play_type == "goal"){
                p.addGoal();
            } else if (play_type == "penalty"){
                p.addPen();
            } else { // error checking
                std::cout << "Your play type is not supported. Here's the broken word: " << play_type << std::endl;
            }
            player_vector.push_back(p);
        } else if (line_index > 5 && curr_word != ")" && play_type == "goal"){ // adds assists
            for (unsigned int i = 0; i < player_vector.size(); i++){ // checks to see if a player exists yet
                if (player_vector[i].getName() == curr_word){
                    player_vector[i].addAssist();
                    continue;
                }
            }
            Player p(curr_word, team_of_line); // adds unique
            p.addAssist();
            player_vector.push_back(p);
        }






    }


}

int main(int argc, char* argv[]){
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

    read_input(input_doc);
    std::cout << player_vector.size() << std::endl;
    for (int l = 0; l<player_vector.size(); l++){
        std::cout << player_vector[l].getName() << std::endl;
    }
    return 0;
}

