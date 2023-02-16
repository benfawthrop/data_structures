//
// Created by Benjamin Fawthrop on 2/13/23.
//

#include "customers.h"

// checks a list to see if the customer is in it
bool Customer::isIn(std::list<Customer*> c_list) {
    std::list<Customer*>::iterator it;
    for (it = c_list.begin(); it != c_list.end(); ++it){
        if (id == (*it)->getID()){
            return true;
        }
    }
    return false;
}

// adds an item to the list of all rented items
void Customer::rent(Inventory *item_to_rent) {
    items_renting.push_back(item_to_rent);
}

// adds an item to the queue for rent
void Customer::queue(Inventory *item_to_rent) {
    items_queued.push_back(item_to_rent);
}

// returns an item
void Customer::returnItem(Inventory *item_to_ret) {
    std::list<Customer*>::iterator it;
    for (it = items_renting.begin(); it != items_renting.end(); ++it){
        if ((*it)->getID() == item_to_ret->getID()){
            break;
        }
    }
    items_renting.erase(it);
}

std::ostream& operator<< (std::ostream& out, const Customer& cust) {
    std::list<Inventory*> renting = cust.getRenting();
    std::list<Inventory*> queue = cust.getQueue();
    out << 'C' << cust.getID() << " " << cust.getName() << std::endl;
    if (renting.size() > 0) {
        out << "Rentals: ";
        std::list<Inventory*>::iterator it = renting.begin();
        int temp = (*it)->getID();
        int count = 0;
        for (it = renting.begin(); it != renting.end(); ++it){
            if ((*it)->getID() == temp){
                count++;
            } else {
                out << "T" << temp << " (" << count << ") ";
                temp = (*it)->getID();
                count = 1;
            }
        }
        out << std::endl;
    }
    if (queue.size() > 0){
        out << "Pending: ";
        std::list<Inventory*>::iterator it = queue.begin();
        int temp = (*it)->getID();
        int count = 0;
        for (it = queue.begin(); it != queue.end(); ++it){
            if ((*it)->getID() == temp){
                count++;
            } else {
                out << "T" << temp << " (" << count << ") ";
                temp = (*it)->getID();
                count = 1;
            }
        }
        out << std::endl;
    }
    out << std::endl;
}