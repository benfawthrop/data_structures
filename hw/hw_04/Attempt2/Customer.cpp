//
// Created by Benjamin Fawthrop on 2/16/23.
//

#include "Customer.h"
#include <iostream>
#include <string>
#include <list>


std::list<int>::iterator Customer::findPlace(int id_to_check, std::list<int> list_to_check){
    std::list<int>::iterator it;
    for (it = list_to_check.begin(); it != list_to_check.end(); ++it){
        if (*it < id_to_check){
            return it;
        }
    }
    it = list_to_check.end();
    return it;
}

void Customer::rentItem(int item_id) {
    std::list<int>::iterator it = findPlace(item_id, items_renting);
    items_renting.insert(it, item_id);
}

void Customer::queueItem(int item_id) {
    std::list<int>::iterator it = findPlace(item_id, items_queued);
    items_queued.insert(it, item_id);
}

bool Customer::returnItem(int item_id) {
    bool owned = false;
    for (std::list<int>::iterator it = items_renting.begin();
            it != items_renting.end(); ++it){
        if (*it == item_id){
            owned = true;
            break;
        }
    }
    if (owned) {
        items_renting.erase(it);
    }
}

void Customer::moveToRenting(int item_id) {
    std::list<int>::iterator it = items_queued.begin();
    rentItem(*it);
    items_queued.erase(it);
}

// overloaded output operator
// outputs both types of items (pending and rentals)
std::ostream& Customer::operator<<(std::ostream &out) {
    out << "C" << id << ' ' << name << std::endl;
    if (items_renting.size() > 0){
        out << "Rentals: ";
        std::list<int>::iterator it = items_renting.begin();
        int temp = *it;
        int count = 0;
        for (it = items_renting.begin(); it != items_renting.end(); ++it){
            if (*it == temp){
                count++;
            } else {
                out << "T" << temp << " (" << count << ") ";
                temp = *it;
                count = 1;
            }
        }
        out << std::endl;
    }
    if (items_queued.size() > 0){
        out << "Pending: ";
        std::list<int>::iterator it = items_queued.begin();
        int temp = *it;
        int count = 0;
        for (it = items_queued.begin(); it != items_queued.end(); ++it){
            if (*it == temp){
                count++;
            } else {
                out << "T" << temp << " (" << count << ") ";
                temp = *it;
                count = 1;
            }
        }
        out << std::endl;
    }
    out << std::endl;
}
