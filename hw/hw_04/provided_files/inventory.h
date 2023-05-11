//
// Created by Benjamin Fawthrop on 2/13/23.
//

#ifndef _ds_inventory_
#define _ds_inventory_
#include <iostream>
#include <string>
#include <list>
#include "customers.h"

class Customer;
class Inventory {
public:
    //constructor
    Inventory(int _id = 0000, int _amnt = 0, std::string _item = "No Name Item"){
        id = _id;
        amount = _amnt;
        item = _item;
    }

    // getters
    int getAmnt() const { return amount; } // returns amount of item in inventory
    int getID() const { return id; } // returns the item ID
    std::string getName() const { return item; } // returns the item name
    // returns the list of renting customers
    std::list<Customer*> getRenting() { return renting_custs; }
    // returns the list of pending customers
    std::list<Customer*> getQueue() { return rental_queue; }
    // finds the place in a given list where a customer object belongs
    std::list<Customer*>::iterator findPlace(
            Customer& id_to_check, std::list<Customer*>& list_to_check);

    // setters
    void rentItem(Customer*& cust); // rents out 1 of the item
    void returnItem(Customer*& cust); // returns an item that a customer had rented
private:
    std::list<Customer*> renting_custs; // list of customers that are currently renting
    std::list<Customer*> rental_queue; // list of all customers waiting for a rental
    int id; // stores the items ID number
    std::string item; // stores the item name
    int amount; // stores the item amount
};

// overloaded << operator
std::ostream& operator<< (std::ostream& out, Inventory& inventory);

#endif //_ds_inventory_
