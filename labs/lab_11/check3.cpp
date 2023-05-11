//
// Created by Benjamin Fawthrop on 4/5/23.
//
#include <vector>
#include <string>
#include <iostream>

typedef std::vector <std::string> DonutBox;

void findBoxes(const DonutBox& box, DonutBox& current_box, std::vector<DonutBox>& boxes){
    if (current_box.size() == box.size()) {
        boxes.push_back(current_box);
        return;
    }
    for (int i = 0; i < box.size(); i++ ) {
        bool can_add = true;
        for (int j = 0; j < current_box.size(); j++) {
            if (box[i] == current_box[j]) {
               can_add = false;
               break;
            }
        }
        if (can_add) {
            current_box.push_back(box[i]);
            findBoxes(box, current_box, boxes);
        }
    }
}

void findBoxes(const DonutBox& box, std::vector<DonutBox>& boxes){
    DonutBox tmp;
    findBoxes( box, tmp, boxes);
}

void printDonutBoxes(const std::vector<DonutBox>& box_to_print) {
    for (int i = 0; i < box_to_print.size(); i++) {
        std::cout << "Box: " << i + 1 << "  ";
        for (int j = 0; j < box_to_print[i].size(); j++) {
            std::cout << box_to_print[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {

    DonutBox donuts;
    std::vector <DonutBox> boxes;
    donuts.push_back("strawberry");
    donuts.push_back("chocolate");
    donuts.push_back("maple");
    findBoxes(donuts, boxes);
    printDonutBoxes(boxes);
}