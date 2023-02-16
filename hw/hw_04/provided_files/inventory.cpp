//
// Created by Benjamin Fawthrop on 2/13/23.
//

#include "inventory.h"

// rents an item out to a customer
void Inventory::rentItem(Customer* cust) {
    if (amount > 0){
        amount--;
        // adds the item and customer to opposing lists
        renting_custs.push_back(cust);
        *cust.rent(*this);
    } else {
        // adds the item and customer to opposing queues
        rental_queue.push_back(cust);
        *cust.queue(*this)
    }
}

// returns an item
void Inventory::returnItem(Customer* cust) {
    std::list<Customer*>::iterator it;
    bool was_renting = false;
    for (it = renting_custs.begin(); it != renting_custs.end(); ++it){
        if (**it.getID() == *cust.getID()){
            was_renting = true;
            break;
        }
    }
    if (was_renting){
        amount++;
        renting_custs.erase(it);
    } else{
        std::cerr << "Customer C" << *cust.getID() <<
                " attempted to return item T" << id << " which she/he did not rent." << std::endl;
    }
}

std::ostream& operator<< (std::ostream& out, const Inventory& inventory){
    out << "T" << inventory.getID() << " " << inventory.getAmnt() << " available "
        << inventory.getName() << std::endl;
    std::list<Customer*> renting = inventory.getRenting();
    std::list<Customer*> pending = inventory.getQueue();
    if (renting.size() > 0){
        out << "Rental Customers: ";
        std::list<Customer*>::iterator it = renting.begin();
        Customer temp = **it;
        int count = 0;
        for (it = renting.begin(); it != renting.end(); +it){
            if ((*it)->getID() == temp.getID()){
                count++;
            } else {
                out << "C" << temp.getID() << " " << temp.getName();
                out << " (" << count << ") ";
                temp = **it;
                count = 1;
            }
        }
        out << std::endl;
    }
    if (pending.size() > 0){
        out << "Pending Customers: ";
        std::list<Customer*>::iterator it = pending.begin();
        Customer temp = **it;
        int count = 0;
        for (it = pending.begin(); it != pending.end(); +it){
            if ((*it)->getID() == temp.getID()){
                count++;
            } else {
                out << "C" << temp.getID() << " " << temp.getName();
                out << " (" << count << ") ";
                temp = **it;
                count = 1;
            }
        }
        out << std::endl;
    }
    out << std::endl;
}
