//
// Created by Benjamin Fawthrop on 2/13/23.
//

#ifndef _ds_customers_
#define _ds_customers_
#include <iostream>
#include <list>
#include "inventory.h"


class Inventory;
class Customer {
public:
    // constructor
    Customer(int _id, std::string _name){
        id = _id;
        name = _name;
    }

    // getters
    int getID() { return id; } // returns customer ID
    std::string getName() { return name; } // returns cust name
    // checks to see if this customer is in a given list
    bool isIn(std::list<Customer*>& c_list);
    // returns the list of rented items
    std::list<Inventory*> getRenting() { return items_renting; }
    // returns the list of queued items
    std::list<Inventory*> getQueue() { return items_queued; }
    // returns an iterator which holds the place in a list for a given item
    std::list<Inventory*>::iterator findPlace(
            Inventory& id_to_check, std::list<Inventory*>& list_to_check);

    // setters
    void rent(Inventory* item_to_rent); // rents an item
    void queue(Inventory* item_to_rent); // queues a given item
    void returnItem(Inventory* item_to_ret); // returns an item from the rental list
    void removePending() { items_queued.pop_front(); } // removes the first queued item

private:
    std::list<Inventory*> items_renting; // list of all items the consumer is currently renting
    std::list<Inventory*> items_queued; // list of all items the consumer is waiting for
    int id; // stores the customers ID number
    std::string name; // stores the customer name
};

// overloaded << operator for printing a customer
std::ostream& operator<< (std::ostream& out, Customer& cust);

#endif //_ds_customers_
