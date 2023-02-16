//
// Created by Benjamin Fawthrop on 2/13/23.
//

#ifndef _ds_inventory_
#define _ds_inventory_
#include <iostream>
#include <string>
#include <list>
#include "customers.h"


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
    std::list<Customer*> getRenting() { return renting_custs; }
    std::list<Customer*> getQueue() { return rental_queue; }

    // setters
    void rentItem(Customer* cust); // rents out 1 of the item
    void returnItem(Customer* cust); // returns an item that a customer had rented
private:
    std::list<Customer*> renting_custs; // list of customers that are currently renting
    std::list<Customer*> rental_queue; // list of all customers waiting for a rental
    int id; // stores the items ID number
    st::string item; // stores the item name
    int amount; // stores the item amount
};

std::ostream& operator<< (std::ostream& out, const Inventory& inventory);

#endif //_ds_inventory_
