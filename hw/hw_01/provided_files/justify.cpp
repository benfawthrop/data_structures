#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

// creates our basic variables
vector<string> words; // stores all of the words from the given txt doc
int col_width; // stores the column width from the command line
string input_file; // store the input file name
string output_file; // stores output file name
string justify_type; // stores the type of justification from the command line
int num_words = 0; // stores a count of the total number of words in `words`

// takes a given string and hyphenates it based on if it is larger than the given col width
// returns the value that should be added, and sets the string_to_use var to what is left
string hyphenate (string& string_to_use, int column){
    if (string_to_use.size() <= column){
        return string_to_use;
    }
    string sub = string_to_use.substr(0, column - 1) + '-'; // hyphenated portion
    string fin = string_to_use.substr(column - 1, string_to_use.size()); // remainder
    string_to_use = fin; //sets the old variable to the remainder
    return sub;
}
// takes in the justify type and creates each line using these standards
string create_line (vector<string>& words, int column, string& justify_type){
    string line = ""; // initializes our final string, which we append stuff onto
    if (justify_type == "flush_left"){
        // justifies left

        while (line.size() < column && num_words > 0){
            // checks if the word needs to be hyphenated, then adds each word to the `line` string
            string tmp = hyphenate(words[0], column);
            if ((line.size() + tmp.size()) <= column){
                line += tmp;
                if (tmp == words[0]){
                    words.erase(words.begin());
                    num_words--;
                    line += ' ';
                }

            } else {break;}
        }
        
        // minor formatting for cases where things dont totally line up
        if (line.size() < column){
            string end(column - line.size(), ' ');
            line += end;
        } else if (line.size() > column){
            line.pop_back();
        }

    } else if (justify_type == "flush_right"){
        // justifies right

        while (line.size() < column && num_words > 0){
            // checks if the word needs to be hyphenated, then adds each word to the `line` string
            string tmp = hyphenate(words[0], column);
            if ((line.size() + tmp.size()) <= column){
                line += tmp;
                if (tmp == words[0]){
                    words.erase(words.begin());
                    num_words--;
                    line += ' ';
                }

            } else {break;}
        }
        
        // formats the string to be right justified in within the `column` width column
        if (line.size() < column){
            line.pop_back();
            
            string end(column - line.size(), ' ');
            line = end + line;
        } else if (line.size() > column){
            line.pop_back();
        } else if (line.size() == column && line.back() == ' '){
            line.pop_back();
            line = ' ' + line;
        }
    } else if (justify_type == "full_justify"){
        // full center justify
        vector<string> line_vector; // stores all of the strings that will be in each line
        int vector_sum = 0; // count for number of total characters in each line
        while (vector_sum < column && num_words > 0){
            // checks to see if the word needs to be hyphenated, then adds each word to our `line_vector`
            string init = words[0];
            string tmp = hyphenate(words[0], column);
            // these are some debugging print statements
            // cout << "our tmp word is: " << tmp << std::endl;
            // cout << "our tmp size is: " << (tmp.size()) << std::endl;
            // cout << "our vector_sum size is: " << vector_sum << std::endl;
            // cout << "our line_vector size is: " << (line_vector.size()) << std::endl;

            if ((line_vector.size() + vector_sum + tmp.size()) <= column){
                line_vector.push_back(tmp);
                vector_sum += tmp.size();
                if (tmp == words[0]){
                    words.erase(words.begin());
                    num_words--;
                }

            } else {
                words[0] = init;
                break;
            }
        }
        if (line_vector.size() == 1){
            // this is the edge case that a line is 1 word long but is shorter than `column`, 
            // it adds the according spaces to the end
            string s (column - line_vector[0].size(), ' ');
            line += line_vector[0];
            line += s;

        } else if (vector_sum < column){
            // regular case where there are multiples smaller words
            int num_spaces = (column - vector_sum); // total number of spaces remaining to be added
            int spaces_in_line = line_vector.size() - 1; // number of times a space needs to be added
            int spaces_per = (num_spaces + (spaces_in_line - 1)) / (spaces_in_line); // this is an integer rep of the number of spaces needed per space
            while (line_vector.size() > 0){
                // adds our word to the line, then checks to see if it needs spaces
                // if it does need spaces, it adds the required spaces to the line
                line += line_vector[0];
                string spaces;

                if (num_spaces > spaces_per){
                    // while there are enough spaces available, we add our divisor rounded up
                    string t (spaces_per, ' ');
                    spaces = t;
                    num_spaces -= spaces_per;
                    spaces_in_line--;
                } else {
                    // if there are not enough spaces available we add our divisor rounded down
                    string t ((num_spaces / spaces_in_line), ' ');
                    spaces = t;
                }
                
                if (line_vector.size() != 1){
                    // adds the spaces
                    line += spaces;
                    
                }
                
                line_vector.erase(line_vector.begin());

            }
            
        } else {
            // this is the case where our word is exactly `column` letters long
            line += line_vector[0];
        }

    }
    return line;
}

// this function opens the file and adds all of the words from that file into the `words` vector
// it also iterates the num_words counter accordingly
void open_file (string& input_file, vector<string>& words, int& num_words){
    std::ifstream infile;
    infile.open(input_file);
    string temp;
    while (infile >> temp){
        words.push_back(temp);
        temp.clear();
        num_words++;
    }
}

// creates the box using the above defined helper functions
void create_box (string& justify_type, vector<string>& words, int column, string& output_file){
    std::ofstream outfile;
    outfile.open(output_file);
    string top_bot ( column + 4, '-' );
    outfile << top_bot << std::endl; // adds the top line
    while (num_words > 0){
        // adds our body of text
        string new_line = create_line(words, column, justify_type);
        outfile << "| " << new_line << " |" << std::endl;
    }
    outfile << top_bot << std::endl; // adds the bot line

}

// takes inputs, opens our file, and creates our box
int main (int argc, char* argv[]){
    input_file = argv[1];
    output_file = argv[2];
    col_width = atoi(argv[3]);
    justify_type = argv[4];
    open_file(input_file, words, num_words);
    create_box(justify_type, words, col_width, output_file);

}


