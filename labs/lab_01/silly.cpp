#include <iostream>
#include <string>


int main(int argc, char* argv[]){
    int final = 1;
    std::cout << argv[1] << std::endl;
    for (int i = 1; i < argc; i++){
        std::string temp = argv[i]; 
        int temp2 = atoi(temp.c_str());
        // std::cout << temp2 << std::endl;
        final *= temp2;
    }
    std::cout << "product of integers:  " << final << std::endl;
    return 0;
}