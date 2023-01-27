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

std::ifstream input_doc;
std::ofstream output_doc;
std::string output_type;

//global variables
std::vector<Player> player_vector;
std::vector<Team> team_vector;

//, std::vector<Player> &player_vector, std::vector<Team> &team_vector
// This function is responsible for taking the input from the given file
void read_input(std::ifstream& in_file){
    // TODO: make it so that it doesn't grab duplicate names
    std::string curr_word; // stores our current word
    std::string team_of_line; // stores what team each statistic is related to so that it can be added to the player
    int word_count = 0; // counts the number of words in order to skip the date
//    bool skip = false; // bool value for if we should skip or not
    int line_index = 0; // stores which word I am on in the current line
    std::string play_type; // stores what type of play the current line is (goal or penalty)
    int final_countdown = 0; // countdown used to skip words
//    std::string team1; // name of our first team (away team)
//    std::string team2; // name of our second team (home team)
//    int team1_score; // score of away team
//    int team2_score; // score of home team
//    int score_countdown;


    while (in_file >> curr_word){
//        if (score_countdown == 4){
//            team1 = curr_word;
//        } else if (score_countdown == 3){
//            team1_score = std::atoi(curr_word);
//        } else if (score_countdown == 2){
//            team2 = curr_word;
//        } else if (score_countdown == 1){
//            team2_score = atoi(curr_word.c_str());
//            for (int j = 0; j < team_vector.size(); j++){
//                if (team_vector[j] )
//            }
//        }

        if (final_countdown > 0){ // iterates our final countdown if it exists
            final_countdown--;
            continue;
        }
        if (curr_word == "OVERTIME"){
            continue;
        }
        word_count++; // these two statements iterate our word count and line index
        line_index++; // to figure out where we are in the line
        if (word_count < 8){ // skips date
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
//            skip = false;
            play_type.clear();
            word_count = 0;
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
            if (curr_word == "BENCH"){
                continue;
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
    }
}

//void create_teams(std::vector<Player>& vec_of_players, std::vector<Team>& vec_of_teams){
//    for (int i = 0; i < vec_of_players.size(); i++){
//        std::string curr_team = vec_of_players[i].getTeam();
//        if (vec_of_teams.size() > 1){
//            for (int j = 0; j < vec_of_teams.size(); j++){
//                vec_of_teams[j].
//            }
//        }
//    }
//}


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
    // TODO: Make the operator function work for alphabetic comparisons as well in order to tie break comparisons
    std::sort(player_vector.begin(), player_vector.end());
    if (output_type == "--player_stats") {
        output_doc << "Player Name" << std::setw((18 - 11) + 2 + 4) << "Team";
        output_doc << std::setw((10 - 4) + 8) << "Goals" << std::setw(9);
        output_doc << "Assists" << std::setw(11) << "Penalties" << std::endl;
        for (unsigned int l = 0; l < player_vector.size(); l++) {
            player_vector[l].printPlayer(18, output_doc);
//        std::cout << player_vector[l].getName() << "  " << player_vector[l].getTeam() << std::endl;
        }
    }
    return 0;
}

