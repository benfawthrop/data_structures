//
// Created by Benjamin Fawthrop on 2/13/23.
//

#ifndef _ds_customers_
#define _ds_customers_
#include <iostream>
#include <list>
#include "inventory.h"


class Customer {
public:
    // constructor
    Customer(int _id, std::string _name){
        id = _id;
        name = _name;
    }

    // getters
    int getID() { return id; }
    std::string getName() { return name; }
    bool isIn(std::list<Customer*> c_list);
    std::list<Inventory*> getRenting() { return items_renting; }
    std::list<Inventory*> getQueue() { return items_queued; }

    // setters
    void rent(Inventory* item_to_rent);
    void queue(Inventory* item_to_rent);
    void returnItem(Inventory* item_to_ret);

private:
    std::list<Inventory*> items_renting; // list of all items the consumer is currently renting
    std::list<Inventory*> items_queued; // list of all items the consumer is waiting for
    int id; // stores the customers ID number
    std::string name; // stores the customer name
};

std::ostream& operator<< (std::ostream& out, const Customer& cust);

#endif //_ds_customers_
