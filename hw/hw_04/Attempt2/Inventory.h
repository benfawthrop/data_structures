//
// Created by Benjamin Fawthrop on 2/16/23.
//

#ifndef DATA_STRUCTURES_INVENTORY_H
#define DATA_STRUCTURES_INVENTORY_H
#include <iostream>
#include <string>
#include <list>
#include "Customer.h"



class Inventory {
public:
    //constructor
    Inventory(int _id = 0000, int _amnt = 0, std::string _item = "No Name Item"){
        id = _id;
        amount = _amnt;
        item = _item;
    }

    // getters
    int getAmnt() const { return amount; }
    int getID() const { return id; }
    std::string getName() const { return item; }
    std::list<int> getRenting() const{ return renting_ids; }
    std::list<int> getQueue() const { return pending_ids; }
    std::list<int>::iterator findPlace(int id_to_check, std::list<int> list_to_check);

    // setters
    void rentItem(int cust_id);
    int returnItem(int cust_id);

    // operators
    std::ostream& operator<< (std::ostream& out);
private:
    std::list<int> renting_ids; // list of IDs of customers renting
    std::list<int> pending_ids; // list of IDs of customers waiting to rent
    int id; // stores the items ID number
    std::string item; // stores the item name
    int amount; // stores the item amount
};


#endif //DATA_STRUCTURES_INVENTORY_H
