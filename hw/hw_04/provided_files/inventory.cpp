//
// Created by Benjamin Fawthrop on 2/13/23.
//

#include "inventory.h"
#include "customers.h"
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>


// This function finds the correct index to add the new customer to
std::list<Customer*>::iterator Inventory::findPlace(
        Customer& id_to_check, std::list<Customer*>& list_to_check){
    std::list<Customer*>::iterator it;
    for (it = list_to_check.begin(); it != list_to_check.end(); ++it){
        // if the id of the customer is < the id of the checked item, stop
        if ((*it)->getID() < id_to_check.getID()){
            return it;
        }
    }
    // base case
    it = list_to_check.end();
    return it;
}


// rents an item out to a customer
void Inventory::rentItem(Customer*& cust) {
    if (amount > 0){
        amount--;
        // adds the item and customer to opposing lists
        std::list<Customer*>::iterator it = findPlace(*cust, renting_custs);
        renting_custs.insert(it, cust);
        cust->rent(this);
    } else {
        // adds the item and customer to opposing queues
        rental_queue.push_back(cust);
        cust->queue(this);
    }
}

// returns an item
void Inventory::returnItem(Customer*& cust) {
    // takes a pointer to a customer as an arg
    std::list<Customer*>::iterator it;
    bool was_renting = false;
    for (it = renting_custs.begin(); it != renting_custs.end(); ++it){
        // checks to make sure the customer was actually renting this item
        if ((*it)->getID() == cust->getID()){
            was_renting = true;
            break;
        }
    }
    if (was_renting){
        // increments our stock, removed the customer from renting
        // moves the next person from the queue to the renting list
        amount++;
        renting_custs.erase(it);
        cust->returnItem(this);
        if (rental_queue.size() > 0){
            std::list<Customer*>::iterator i = rental_queue.begin();
            rentItem(*i);
            rental_queue.erase(i);
        }
    } else{
        // throws error if it wasn't being rented
        std::cerr << "Customer C" << cust->getID() <<
                " attempted to return item T" << id << " which she/he did not rent." << std::endl;
    }
}

// overloaded << operator responsible for printing out each inventory item
std::ostream& operator<< (std::ostream& out, Inventory& inventory){
    // outputs the Item ID, Amount available, and name
    out << "T" << inventory.getID() << " " << inventory.getAmnt() << " available "
        << inventory.getName() << std::endl;
    // grabs rental and queued lists
    std::list<Customer*> renting = inventory.getRenting();
    std::list<Customer*> pending = inventory.getQueue();
    if (renting.size() > 0){
        // if there are renting customers, all of them are printed out
        out << "Rental Customers: ";
        std::list<Customer*>::iterator it = renting.begin();
        Customer temp = **it;
        int count = 0;
        for (it = renting.begin(); it != renting.end(); ++it){
            // iterates through all customers, counting them, and printing them
            // when necessary
            if ((*it)->getID() == temp.getID()){
                count++;
            } else {
                out << "C" << std::setfill('0') << std::setw(4) <<
                        temp.getID() << " " << temp.getName();
                out << " (" << count << ") ";
                temp = **it;
                count = 1;
            }
        }
        // makes sure the last item gets printed
        out << "C" << std::setfill('0') << std::setw(4) <<
                temp.getID() << " " << temp.getName();
        out << " (" << count << ") ";

        out << std::endl;
    }
    if (pending.size() > 0){
        // if there are pending customers, all of them are printed out
        out << "Pending Customers: ";
        std::list<Customer*>::iterator it = pending.begin();
        Customer temp = **it;
        int count = 0;
        for (it = pending.begin(); it != pending.end(); ++it){
            // iterates though all pending customers, counting them
            // and printing them when necessary
            if ((*it)->getID() == temp.getID()){
                count++;
            } else {
                out << "C" << temp.getID() << " " << temp.getName();
                out << " (" << count << ") ";
                temp = **it;
                count = 1;
            }
        }
        // makes sure the last item gets printed
        out << "C" << std::setfill('0') << std::setw(4) <<
                temp.getID() << " " << temp.getName();
        out << " (" << count << ") ";
        out << std::endl;
    }
    return out;
}
