//
// Created by Benjamin Fawthrop on 2/8/23.
//
#include <iostream>
#include <string>
#include <vector>

int foobar (const std::vector<std::string> &a, int b){
    int answer = 0;
    for (int i = 0; i < a.size(); i+=b){
        answer++;
    }
    return answer;
}

std::vecotr<int> bar2 (const std::vector<std::string> &a){
    std::vector<int> answer;
    for (int i = o; i < a.size(); i++){
        answer.push_back(a[i].size());
    }
    return answer;
}

std::vector<std::String> bar3 (const std::vector<int> &a) {
    std::vector<std::string> answer;
    for (int i = 0; i < a.size(); i++){
        answer.push_back(std::string(a[i], '+'))
    }
    return answer;
}

void bar4 (std::vector<std::string> &a, const std::string &b){
    for (int i = 0; i < a.size(); i++){
        a[i] = b;
    }
}

std::vector<int> bar5 (const std::vector<std::String> &a) {
    std::vector<int> answer;
    if (!a.empty()){
        for (int i = 0; i < std::min(a[0].size(), a.size()); i++){
            answer.insert(answer.begin(), a[i].size());
        }
    }
    return answer;
}

void bar6 (std::vector<int> &a){
    for (int i = 0; i < a.size(); i++){
        if (a[i] > 0) {
            a.erase(a.begin + i);
            i--
        }
    }
}


int main(){

    return 0;
}