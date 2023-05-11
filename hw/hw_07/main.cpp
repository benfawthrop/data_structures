#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Fighter.h"
//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

void getQueries(std::map<std::string, Fighter> &fighters_map, std::string m_names[7],
                std::ifstream &queries, std::ofstream &outfile, std::map<std::string, std::set<Fighter> > &move_map) {
    // this segment of code orders the move names for our -q inquiry
    std::set<std::string> m_names_set;
    for (int j = 0; j < 7; j++) {
        m_names_set.insert(m_names[j]);
    }

    std::string type;
    while (queries >> type) {
        // loop through whole query doc
        if (type == "-q") {
            std::string character, move;
            queries >> character >> move;
            // error checks for character and move variables
            if (fighters_map.find(character) == fighters_map.end() ) {
                outfile << "Invalid character name: " << character << std::endl << std::endl;
                continue;
            }
            if (move_map.find(move) == move_map.end() && move != "all") {
                outfile << "Invalid move name: " << move << std::endl << std::endl;
                continue;
            }
            // outputs the move speeds
            if (move != "all") {
                // if move is specified
                outfile << character << ' ' << move << ": " <<
                        fighters_map[character].move_speeds[move] << std::endl;
            } else {
                // if move isn't specified
                std::set<std::string>::iterator it = m_names_set.begin();
                for (; it != m_names_set.end(); ++it) {
                    outfile << character << ' ' << *it << ": " <<
                            fighters_map[character].move_speeds[*it] << std::endl;
                }
            }
        } else if (type == "-f") {
            std::string move;
            int lim;
            queries >> move >> lim;
            // error checks our move variable
            if (move_map.find(move) == move_map.end()) {
                outfile << "Invalid move name: " << move << std::endl << std::endl;
                continue;
            }
            // outputs our fastest characters based on the conventions in the assignment
            outfile << type << " " << move << " " << lim << std::endl;
            std::set<Fighter>::iterator it = move_map[move].begin();
            for (int i =0; i < lim; i++, ++it) {
                outfile << it->getName() << " " << it->getMoveSpeed(move) << std::endl;
            }
        } else if (type == "-s") {
            std::string move;
            int lim;
            queries >> move >> lim;
            // error checks our move variable
            if (move_map.find(move) == move_map.end()) {
                outfile << "Invalid move name: " << move << std::endl << std::endl;
                continue;
            }
            // outputs our slowest characters based on the conventions in the assignment
            outfile << type << " " << move << " " << lim << std::endl;
            std::set<Fighter>::reverse_iterator it = move_map[move].rbegin();
            for (int i =0; i < lim; i++, ++it) {
                outfile << it->getName() << " " << it->getMoveSpeed(move) << std::endl;
            }
        } else if (type == "-d") {
            std::string move;
            int time;
            queries >> move >> time;
            // error checks our move variable
            if (move_map.find(move) == move_map.end()) {
                outfile << "Invalid move name: " << move << std::endl << std::endl;
                continue;
            }
            // outputs all the characters that have time move speed for move
            outfile << type << " " << move << " " << time << std::endl;
            std::set<Fighter>::iterator it = move_map[move].begin();
            for (; it != move_map[move].end(); ++it) {
                if (it->getMoveSpeed(move) == time)
                    outfile << it->getName() << std::endl;
            }
        }
        outfile << std::endl;
    }
}

int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

    ///////Fill in the rest of main below:

    // data structures for our functions
    std::map<std::string, Fighter> fighter_map;
    std::map<std::string, std::set<Fighter> > fighter_by_moves;
    // gets database
    fighter_map = getFrameData(dbfile,
                               const_cast<std::string *>(move_names), fighter_by_moves);
    // gets inputs, and prints outputs
    getQueries(fighter_map, const_cast<std::string *>(move_names),
               infile, outfile, fighter_by_moves);


	return 0;
}
