//
// Created by Benjamin Fawthrop on 2/14/23.
//

#include <iostream>
#include <ostream>
#include <algorithm>
#include "inventory.h"
#include "customers.h"


void addCust(std::list<Customer*> list_to_use, Customer* cust){
    std::list<Customer*>::iterator it;
    for (it = list_to_use.begin(); it != list_to_use.end(); ++it){
        if (cust.getID() <= (*it)->getID()){
            list_to_use.insert(it, cust);
        }
    }

}

std::list<Inventory*> getInventory(std::ifstream & infile){
    std::list<Inventory*> list_of_inventory;
    std::string id_str;
    while (infile >> id_str){
        int amount;
        std::string item_name;
        infile >> amount >> item_name;
        int id = atoi(id_str.substr(1, 4));
        if (id_str[0] != 'T'){
            std::cerr << "Invalid inventory ID " << id << " found in the inventory file." << std::endl;
            id_str.clear();
            continue;
        }
        Inventory* next = new Inventory(id, amount, item_name);
        list_of_inventory.push_back(next);
        id_str.clear()
    }
}
bool findTool(std::list<Inventory*> tool_list, int tool_id, std::list<Inventory*>::iterator it){
    for (it = tool_list.begin(); it != tool_list.end(); ++it){
        if ((*it)->getID() == tool_id){
            return true;
        }
    }
    return false;
}

std::list<Customer*> getCustomers(std::ifstream & infile, std::list<Inventory*> inv_list){
    std::list<Customer*> list_of_customers;
    std::string cust_id_str;
    while (infile >> cust_id_str){
        int amount, time_stamp;
        std::string trans_type, item_id_str, name;
        infile >> trans_type >> time_stamp >> amount >> item_id_str >> name;
        int item_id = atoi(item_id_str.substr(1, 4));
        int cust_id = atoi(cust_id_str.substr(1, 4));
        if (id_str[0] != 'C'){
            std::cerr << "Invalid customer information found for ID " << id <<
                " in the customer file." << std::endl;
            cust_id_str.clear();
            continue;
        }
        Customer* temp = new Customer(cust_id, name);
        bool is_duplicate = temp->isIn(list_of_customers);
        if (!is_duplicate){
            addCust(list_of_customers, temp);
        }
        if (trans_type == "rent") {
            for (int i = 0; i < amount; i++) {
                std::list<Inventory *>::iterator it;
                bool tool_exists = findTool(inv_list, item_id, it);
                if (!tool_exists) {
                    std::cerr << "Customer C" << cust_id << " requested item T" <<
                              item_id << " which is not in the inventory." << std::endl;
                    break;
                }
                (*it)->rentItem(temp);
            }
        } else if (trans_type == "return"){
            for (int i = 0; i < amount; i++) {
                std::list<Inventory *>::iterator it;
                bool tool_exists = findTool(inv_list, item_id, it);
                if (!tool_exists) {
                    std::cerr << "Customer C" << cust_id << " attempted to return item T" <<
                              item_id << " which is not in the inventory." << std::endl;
                    break;
                }
                (*it)->returnItem(temp);
            }
        }
    }
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

}
