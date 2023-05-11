//
// Created by Benjamin Fawthrop on 2/16/23.
//

#ifndef DATA_STRUCTURES_CUSTOMER_H
#define DATA_STRUCTURES_CUSTOMER_H
#include <iostream>
#include <string>
#include <list>


class Customer {
public:
    // constructor
    Customer(int _id, std::string _name){
        id = _id;
        name = _name;
    }

    // getters
    int getID() const { return id; }
    std::string getName() const { return name; }
    std::list<int> getRenting() const { return renting_ids; }
    std::list<int> getQueue() const { return pending_ids; }
    std::list<int>::iterator findPlace(int id_to_check, std::list<int> list_to_check);

    // setters
    void rentItem(int item_id);
    void queueItem(int item_id);
    bool returnItem(int item_id);
    void moveToRenting(int item_id);

    // operators
    std::ostream& operator<< (std::ostream& out);

private:
    std::list<int> items_renting; // list of all item IDs consumer is currently renting
    std::list<int> items_queued; // list of all item IDs consumer is waiting for
    int id; // stores the customers ID number
    std::string name; // stores the customer name
};


#endif //DATA_STRUCTURES_CUSTOMER_H
