//
// Created by Benjamin Fawthrop on 4/9/23.
//

#ifndef HW_09_GENOME_HASH_H
#define HW_09_GENOME_HASH_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

// nodes that store the genome and its position
class hash_node {
public:
    // constructors

    // default
    hash_node() {genome = "";}

    // regular usage
    hash_node(const std::string& g, const int &i) : genome(g) { index.push_back(i); }
    // copy
    hash_node(const hash_node& other) : index(other.index), genome(other.genome) {}

    std::vector<int> index; // stores index position of string in the genome
    std::string genome; // actual string that stores the data in the node
};


// actual hash table class
class genome_hashtable {
public:
    // constructors
    // default (has default args
    genome_hashtable(const int &k, const int &N = 100, const float &f = 0.5);

    // getters
    int kmer() const { return k_len; } // returns kmer size
    int size() const { return actual_size; } // returns size
    float occupancy() const { return occ; } // returns occupancy
    hash_node operator[](std::string str); // indexing to find the element

    // setters
    void insert(hash_node &to_add); // insert a given element into the hashtable
    void resizeTable(int new_size); // resizes and rehashes the table

private:
    std::vector<hash_node> sequences; // actual top level structure of the hash table

    int k_len, table_size, actual_size;
    float occ;

    // private functions
    int getIndex(std::string &str); // uses functor to get an index in the vector to add at
};


// I took this string hash function from lab 11
class hash_string_obj {
public:

    // ----------------------------------------------------------
    // EXPERIMENT WITH THE HASH FUNCTION FOR CHECKPOINT 1, PART 2

    unsigned int operator() ( const std::string& key ) const {
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        //
        //  This is a general-purpose, very good hash function for strings.
        unsigned int hash = 1315423911;
        for(unsigned int i = 0; i < key.length(); i++)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }

};

#endif //HW_09_GENOME_HASH_H
