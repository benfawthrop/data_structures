//
// Created by Benjamin Fawthrop on 2/16/23.
//

#include "Inventory.h"
#include "Customer.h"
#include <iostream>
#include <string>
#include <list>

// This function finds the correct index to add the new customer to
std::list<int>::iterator Inventory::findPlace(int id_to_check, std::list<int> list_to_check){
    std::list<int>::iterator it;
    for (it = list_to_check.begin(); it != list_to_check.end(); ++it){
        if (*it < id_to_check){
            return it;
        }
    }
    it = list_to_check.end();
    return it;
}

// This function takes the ID of a customer and adds it to the appropriate list based on
// if there is stock of the requested item
void Inventory::rentItem(int cust_id) {
    if (amount > 0){
        // rents if available
        amount--;
        std::list<int>::iterator it = findPlace(cust_id, renting_ids);
        renting_ids.insert(it, cust_id);
    } else {
        // queues if not available
        pending_ids.push_back(cust_id);
    }
}

/*
 * Checks if the customer with the ID cust_id is renting the current object
 * if the cust isnt renting, it throws an error and returns -1
 * if the cust is renting, we add 1 to our inventory, remove
 * that cust from the renting list, and adds our first pending
 * customer to the rental list
 *
 * the return value tells is the ID of the customer who was moved
 * from pending to renting.  A -1 return value means that there are
 * no people in the queue, and no action is required
 */
int Inventory::returnItem(int cust_id) {
    std::list<int>::iterator it;
    bool isin = false;
    // checks if the item is owned by the given customer
    for (it = renting_ids.begin(); it != renting_ids.end(); ++it){
        if (*it == id_to_check){
             isin = true;
             break;
        }
    }
    if (!isin){
        // if not owned this error is thrown
        std::cerr << "Customer C" << cust_id <<
                  " attempted to return item T" << id << " which she/he did not rent." << std::endl;
    } else {
        // if owned, it returns the item, increments the amount available
        // and checks if there are other customers waiting
        amount++;
        renting_ids.erase(it);
        if (pending_ids.size() > 0){
            std::list<int>::iterator i = pending_ids.begin();
            rentItem(*i);
            pending_ids.erase(i);
            return *i;
        }
    }
    return -1; // convention
}

// TODO: WRITE THIS FUNCTION
std::ostream& Inventory::operator<< (std::ostream& out){

}
