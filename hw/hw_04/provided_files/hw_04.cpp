//
// Created by Benjamin Fawthrop on 2/14/23.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iomanip>
#include "customers.h"
#include "inventory.h"


// adds a customer to a given list
void addCust(std::list<Customer*>& list_to_use, Customer* cust){
    std::list<Customer*>::iterator it;
    for (it = list_to_use.begin(); it != list_to_use.end(); ++it){
        // finds the place in the given list that the customer belongs
        if (cust->getID() <= (*it)->getID()){
            // inserts the customer
            list_to_use.insert(it, cust);
            return;
        }
    }
    // base case
    list_to_use.push_back(cust);
}

// adds an item to a given list
void addItems(std::list<Inventory*>& list_to_use, Inventory* item){
    std::list<Inventory*>::iterator it;
    for (it = list_to_use.begin(); it != list_to_use.end(); ++it){
        // finds the place in the given list that the item belongs
        if (item->getID() <= (*it)->getID()){
            // inserts the item
            list_to_use.insert(it, item);
            return;
        }
    }
    // base case
    list_to_use.push_back(item);
}

// iterates through the inventory list to build the inventory class
std::list<Inventory*> getInventory(std::ifstream & infile){
    std::list<Inventory*> list_of_inventory;
    std::string id_str;
    while (infile >> id_str){
        int amount;
        std::string item_name;
        infile >> amount >> item_name;
        // turns the ID into an int
        int id = stoi(id_str.substr(1, 4));
        if (id_str[0] != 'T'){
            // throws an error if the ID is invalid
            std::cerr << "Invalid inventory ID " << id << " found in the inventory file." << std::endl;
            id_str.clear();
            continue;
        }
        // allocates memory for a inventory object
        Inventory* next = new Inventory(id, amount, item_name);
        // adds the item
        addItems(list_of_inventory, next);
        id_str.clear();
    }
    return list_of_inventory;
}

// finds the place in a list of Inventory* where a tool is
// returns if the item exists or not
bool findTool(std::list<Inventory*>& tool_list, int tool_id, std::list<Inventory*>::iterator& it){
    for (it = tool_list.begin(); it != tool_list.end(); ++it){
        if ((*it)->getID() == tool_id){
            return true;
        }
    }
    return false;
}

// iterates through our customer in file to get all customers
std::list<Customer*> getCustomers(std::ifstream & infile, std::list<Inventory*> & inv_list){
    std::list<Customer*> list_of_customers;
    std::string cust_id_str;
    while (infile >> cust_id_str){
        // loops through whole file
        int amount, time_stamp;
        std::string trans_type, item_id_str, name;
        infile >> trans_type >> time_stamp >> amount >> item_id_str >> name;
        int item_id = stoi(item_id_str.substr(1, 4));
        int cust_id = stoi(cust_id_str.substr(1, 4));
        if (cust_id_str[0] != 'C'){
            // throws error if ID is invalid
            std::cerr << "Invalid customer information found for ID " << cust_id <<
                " in the customer file." << std::endl;
            cust_id_str.clear();
            continue;
        }
        // allocates memory for the new customer
        Customer* temp = new Customer(cust_id, name);
        // checks if the customer exists yet
        bool is_duplicate = temp->isIn(list_of_customers);
        if (!is_duplicate){
            // adds customer
            addCust(list_of_customers, temp);
        }
        if (trans_type == "rent") {
            // rents the given item the given number of times
            for (int i = 0; i < amount; i++) {
                std::list<Inventory *>::iterator it;
                bool tool_exists = findTool(inv_list, item_id, it);
                if (!tool_exists) {
                    // throws error if the item is not real
                    std::cerr << "Customer C" << cust_id << " requested item T" <<
                              item_id << " which is not in the inventory." << std::endl;
                    break;
                }
                // rents the item
                (*it)->rentItem(temp);
            }
        } else if (trans_type == "return"){
            // returns the item the given number of times
            for (int i = 0; i < amount; i++) {
                std::list<Inventory *>::iterator it;
                bool tool_exists = findTool(inv_list, item_id, it);
                if (!tool_exists) {
                    // throws an error if the item is not real
                    std::cerr << "Customer C" << cust_id << " attempted to return item T" <<
                              item_id << " which is not in the inventory." << std::endl;
                    break;
                }
                // returns the item
                (*it)->returnItem(temp);
            }
        }
    }
    return list_of_customers;
}

int main(int argc, char* argv[]){
    // gets inputs and checks to see if there are enough of them
    if (argc != 5){
        std::cerr << "Not the correct amount of command line args given, needs 4" << std::endl;
        return 1;
    }

    // in/out files
    std::ifstream inventory_in_file;
    std::ifstream customer_in_file;
    std::ofstream inventory_out_file;
    std::ofstream customer_out_file;

    // error checking
    inventory_in_file.open(argv[1]);
    if (!inventory_in_file){
        std::cerr << "Error on input inventory file" << std::endl;
        return 1;
    }
    customer_in_file.open(argv[2]);
    if (!customer_in_file){
        std::cerr << "Error on input customer file" << std::endl;
        return 1;
    }
    inventory_out_file.open(argv[3]);
    if (!inventory_out_file){
        std::cerr << "Error on output inventory file" << std::endl;
        return 1;
    }
    customer_out_file.open(argv[4]);
    if (!customer_out_file){
        std::cerr << "Error on output customer file" << std::endl;
        return 1;
    }
    // gets lists
    std::list<Inventory*> inventory = getInventory(inventory_in_file);
    std::list<Customer*> customers = getCustomers(customer_in_file, inventory);


    // prints out all inventory objects
    for (std::list<Inventory*>::iterator it = inventory.begin();
            it != inventory.end(); ++it){
        inventory_out_file << **it << std::endl;
    }

    // prints out all customers
    for (std::list<Customer*>::iterator it = customers.begin();
            it != customers.end(); ++it){
        customer_out_file << **it << std::endl;
    }

    // deallocating memory
    for (std::list<Inventory*>::iterator it = inventory.begin();
         it != inventory.end(); ++it){
        delete *it;
    }

    for (std::list<Customer*>::iterator it = customers.begin();
         it != customers.end(); ++it){
        delete *it;
    }

    return 0;
}
