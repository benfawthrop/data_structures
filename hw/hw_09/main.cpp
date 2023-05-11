//
// Created by Benjamin Fawthrop on 4/8/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "genome_hash.h"


void buildHashTable(std::string &database, genome_hashtable &table) {
    size_t k = table.kmer();
    // changed here
    for (size_t i = 0; i < database.size(); i++) {
        if (i < k) continue; // makes sure that we stay in bounds
        // grabs our position and k-mer
        int pos = i - k;
        std::string temp = database.substr(pos, k);
        // creates the node to be added to the table
        hash_node to_add(temp, pos);
        table.insert(to_add); // inserts the node
    }
}


void getInputs(int &kmer, int &table_size, float &occupancy,
               std::ifstream &db, std::string &db_str) {
    // Gets the initial inputs we need for the bulk of the program
    std::string temp;
    while (std::cin >> temp) {
        // gets all the information needed for queries
        if (temp == "genome") {
            std::cin >> temp;
            // opens the database file and error checks it
            // to make sure it's a valid file
            db.open(temp);
            if (!db) {
                std::cerr << "There was an error with your database file: "
                          << temp << std::endl;
                return;
            }
            // creates a string of the database for indexing later on
            std::string t;
            while (db >> t) {
                db_str += t;
            }
        } else if (temp == "table_size") {
            std::cin >> table_size;
        } else if (temp == "occupancy") {
            std::cin >> occupancy;
        } else if (temp == "kmer") {
            std::cin >> kmer;
        } else if (temp == "quit") {
            exit(0);
        } else {
            return;
        }
    }
}


// solves for one query
void oneQuery(std::string &query, int num_errors, std::string &db,
              genome_hashtable &table) {
    // formatting print statements
    std::cout << "Query: " << query << std::endl;
    hash_node current = table[query.substr(0, table.kmer())];
    if (current.genome.empty()) {
        std::cout << "No Match" << std::endl;
    }
    int times_outputted = 0;
    // changed here
    for (size_t j = 0; j < current.index.size(); j++) {
        // gets the section of the database where a match might occur
        std::string section = db.substr(current.index[j], query.size());
        int mismatches = 0; // # of mismatches
        for (size_t i = table.kmer(); i < query.size(); i++) {
            // iterates through the two strings to find mismatches
            if (section[i] != query[i]) {
                mismatches++;
            }
        }

        // if we are under the threshold we print it out
        if (mismatches <= num_errors) {
            times_outputted++;
            std::cout << current.index[j] << " " << mismatches << " ";
            std::cout << section << std::endl;
        }
    }
    // if no matches are found, say so
    if (times_outputted == 0) {
        std::cout << "No Match" << std::endl;
    }
}

void getAllQueries(std::string &db_str, genome_hashtable &table) {
    std::string temp;
    int num_errors; // stores number of allowable errors
    std::string query; // stores query string
    while (std::cin >> num_errors) {
        std::cin >> query;
        // checks database for the query sub-genome
        oneQuery(query, num_errors, db_str, table);
        std::cin >> temp;
        // runs unless the user enters quit
        if (temp != "query") exit(0);
    }
}

int main() {
    // vars needed for the program
    std::ifstream in_file;
    std::ifstream database;
    std::ofstream output;
    int table_size, kmer = 0;
    float occupancy = 0.0;
    std::string db_str;


    // main function calls
    getInputs(kmer, table_size, occupancy, database, db_str);
    genome_hashtable table(kmer, table_size, occupancy);
    buildHashTable(db_str, table);
    getAllQueries(db_str, table);


    return 0;
}