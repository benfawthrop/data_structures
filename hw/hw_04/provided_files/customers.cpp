//
// Created by Benjamin Fawthrop on 2/13/23.
//

#include "inventory.h"
#include "customers.h"
#include <list>
#include <iostream>
#include <iomanip>

// This function finds the correct index to add the new customer to
std::list<Inventory*>::iterator Customer::findPlace(
        Inventory& id_to_check, std::list<Inventory*>& list_to_check){
    std::list<Inventory*>::iterator it;
    for (it = list_to_check.begin(); it != list_to_check.end(); ++it){
        // finds the place where it is greater than the current item
        if ((*it)->getID() < id_to_check.getID()){
            return it;
        }
    }
    // base case
    it = list_to_check.end();
    return it;
}


// checks a list to see if the customer is in it
bool Customer::isIn(std::list<Customer*>& c_list) {
    std::list<Customer*>::iterator it;
    for (it = c_list.begin(); it != c_list.end(); ++it){
        if (id == (*it)->getID()){
            return true;
        }
    }
    return false;
}

// adds an item to the list of all rented items
void Customer::rent(Inventory* item_to_rent) {
    std::list<Inventory*>::iterator it = findPlace(*item_to_rent, items_renting);
    items_renting.insert(it, item_to_rent);
    if (items_queued.size() > 0 && item_to_rent->getID() == items_queued.front()->getID()){
        // if the item is being moved from pending to renting, the queued item is removed
        this->removePending();
    }
}

// adds an item to the queue for rent
void Customer::queue(Inventory* item_to_rent) {
    items_queued.push_back(item_to_rent);
}

// returns an item from its purchased list
void Customer::returnItem(Inventory* item_to_ret) {
    std::list<Inventory*>::iterator it;
    for (it = items_renting.begin(); it != items_renting.end(); ++it){
        if ((*it)->getID() == item_to_ret->getID()){
            items_renting.erase(it);
            return;
        }
    }
    items_renting.pop_back();

}

// overloaded << operator which is responsible for printing a customer and all of its items
std::ostream& operator<< (std::ostream& out, Customer& cust) {
    // grabs both rental and queued items
    std::list<Inventory*> renting = cust.getRenting();
    std::list<Inventory*> queue = cust.getQueue();
    // outputs the name and ID of the customer
    out << 'C' << std::setfill('0') << std::setw(4)
            << cust.getID() << " " << cust.getName() << std::endl;
    if (renting.size() > 0) {
        // if renting items, print out each item ID and amount rented
        out << "Rentals: ";
        std::list<Inventory*>::iterator it = renting.begin();
        int temp = (*it)->getID();
        int count = 0;
        for (it = renting.begin(); it != renting.end(); ++it){
            // iterates though every rented item, counting them
            // and printing them when necessary
            if ((*it)->getID() == temp){
                count++;
            } else {
                out << "T" << std::setfill('0') << std::setw(4) <<
                        temp << " (" << count << ") ";
                temp = (*it)->getID();
                count = 1;
            }
        }
        // makes sure the last item gets printed
        out << "T" << std::setfill('0') << std::setw(4) <<
                temp << " (" << count << ") ";
        out << std::endl;
    }
    if (queue.size() > 0){
        // if waiting for items, print out each item ID and amount rented
        out << "Pending: ";
        std::list<Inventory*>::iterator it = queue.begin();
        int temp = (*it)->getID();
        int count = 0;
        for (it = queue.begin(); it != queue.end(); ++it){
            // iterates through the queue, counting amounts for each item,
            // and printing them when necessary
            if ((*it)->getID() == temp){
                count++;
            } else {
                out << "T" << std::setfill('0') << std::setw(4)
                        << temp << " (" << count << ") ";
                temp = (*it)->getID();
                count = 1;
            }
        }
        // makes sure the last item gets printed
        out << "T" << std::setfill('0') << std::setw(4) <<
                temp << " (" << count << ") ";
        out << std::endl;
    }
    return out;
}