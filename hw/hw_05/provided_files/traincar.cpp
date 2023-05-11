// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "traincar.h"

// helper fxn that removes the first element of a train, returning it
TrainCar* PopFront(TrainCar* &head) {
    TrainCar* node = head;
    head = head->next;
    node->next = nullptr;
    return node;
}

// helper fxn that removes the last element of a train, returning it
TrainCar* PopBack(TrainCar* &head) {
    TrainCar* node = head;
    while (node->next->next != nullptr) {
        node = node->next;
    }
    TrainCar* to_return = node->next;
    node->next = nullptr;
    return to_return;
}

// counts the number of engines in a given train
int CountEngines(TrainCar* &head) {
    TrainCar* current = head;
    int count = 0;
    while (current != nullptr) {
        // counts  only if the current car is an engine until there are no more nodes
        if (current->isEngine()) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// adds a new node to the end of the train
void PushBack(TrainCar* &head, TrainCar* car_to_add) {
    // if the list has a length of 0, the head points to the new car
    if (head == nullptr) {
        head = car_to_add;
        return;
    }

    // loops through the linked list till we hit the last node
    TrainCar* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    // sets the pointer of the last node to point to our new last node
    // and sets the previous pointer of the new node to the old last
    temp->next = car_to_add;
    car_to_add->prev = temp;
    car_to_add->next = nullptr;
}

// deallocates all the memory of a train
void DeleteAllCars(TrainCar* &head) {
    // kills the rest of the function if the head doesn't contain a train
    if (head == nullptr) { return; }

    // loops through the whole list deallocating each node
    TrainCar* current = head;
    while (current != nullptr) {
        TrainCar* next = current->next;
        delete current;
        current = next;
    }
    // sets the head pointer to null for convention
    head = nullptr;
}

// calculates the speed of a given train
float CalculateSpeed(TrainCar* &head) {
    TrainCar* current = head;
    float total_weight = 0; // stores total weight of the train
    float total_hp = 0; // stores total hp of the train

    while (current != nullptr) {
        if (current->isEngine()){
            // if the train car is an engine, add horsepower
            total_hp += 3000;
        }
        // increment weight
        total_weight += current->getWeight();
        current = current->next;
    }

    return (total_hp * 550 * 3600) / (20 * 2 * 5280 * total_weight);
}

// most of our basic statistics calculations are done by this function
void TotalWeightAndCountCars(TrainCar* &head, int &total_weight, int &num_engines,
                             int &num_freight, int &num_passenger, int &num_dining,
                             int &num_sleeping) {
    // sets all variables to 0 because in main they are undeclared
    total_weight = 0;
    num_engines = 0;
    num_freight = 0;
    num_passenger = 0;
    num_dining = 0;
    num_sleeping = 0;
    TrainCar* current = head;
    while (current != nullptr) {
        // loops through each train car and increments the arguments
        // accordingly
        if (current->isEngine()){
            num_engines++;
        } else if (current->isFreightCar()){
            num_freight++;
        } else if (current->isPassengerCar()){
            num_passenger++;
        } else if (current->isDiningCar()){
            num_dining++;
        } else if (current->isSleepingCar()){
            num_sleeping++;
        }
        total_weight += current->getWeight();
        current = current->next;
    }
}

// calculates the avg distance from passenger cars to dining cars
float AverageDistanceToDiningCar(TrainCar* &head) {
    float total_distance = 0;
    float num_cars = 0;
    for (TrainCar* current = head; current != nullptr; current = current->next){
        // loops through the whole train
        if (current->isPassengerCar()) {
            // if we hit a passenger, we start counting its distance
            TrainCar* curr_pass = current;
            bool hit_dining = false;
            float count = 0;
            for (TrainCar* p = curr_pass->next; p != nullptr; p = p->next) {
                // loops until we either cannot walk
                if (p->isEngine() || p->isFreightCar()) {
                    return -1;
                }
                count++;
                if (p->isDiningCar()) {
                    // if we hit dining, break
                    hit_dining = true;
                    break;
                }
            }
            if (hit_dining) {
                // increments our total distance
                num_cars++;
                total_distance += count;
            }

        } else if (current->isDiningCar()) {
            // counts from dining car back
            float count = 0;
            for (TrainCar* p = current->next; p != nullptr; p = p->next) {
                // loops until we hit either the end or an illegal car, counting
                // distances from passenger to dining along the way
                count++;
                if (p->isEngine() || p->isFreightCar()) {
                    break;
                } else if (p->isDiningCar()) {
                    break;
                } else if (p->isPassengerCar()) {
                    num_cars++;
                    total_distance += count;
                }
            }
        }
    }
    return total_distance / num_cars;

}


// finds the closest engine piece to a sleeper car
int ClosestEngineToSleeperCar(TrainCar* &head) {
    int count_front = 0; // count from an engine backwards
    int count_back = 0; // count from a sleeper backwards
    bool hit_sleeper = false; // stores if a sleeper car has been hit yet
    bool hit_engine_back = false; // stores if the function has hit an engine from the back yet
    for (TrainCar* current = head; current != nullptr; current = current->next){
        // loops through the whole train
        if (current->isEngine()) {
            // when we find an engine, we tell the function that we have found an engine
            if (hit_sleeper) {
                hit_engine_back = true;
            } else {
                count_front = 0;
            }
        } else if (current->isSleepingCar()) {
            // if we hit a sleeper then we start counting from the back
            count_back = 0;
            hit_sleeper = true;
        }
        if (hit_sleeper) {
            if (!hit_engine_back) {
                // counts if we haven't already calculated the distance
                count_back++;
            }
        } else {
            // increments our front count counter
            count_front++;
        }
    }
    if (hit_engine_back) {
        return std::min(count_back, count_front);
    }
    return count_front;
}

// simple helper function that returns the length of a given train
int FindTrainLength(TrainCar* &head) {
    TrainCar* current = head;
    int count = 0;
    while (current != nullptr) {
        // counts until there are no more nodes
        count++;
        current = current->next;
    }
    return count;
}


std::vector<TrainCar*> ShipFreight(TrainCar* &e_head, TrainCar* &f_head,
                                   int min_speed, int max_cars) {
    std::vector<TrainCar*> final_vector; // vector of trains that we return
    int num_freight = FindTrainLength(f_head); // counts freight cars
    int num_engines = FindTrainLength(e_head); // counts engine cars
    while (num_engines > 0) {
        // loops until there are no more engines
        TrainCar* current_head = nullptr; // head node of the current train
        PushBack(current_head, PopFront(e_head));
        current_head->prev = NULL; // makes sure the head doesn't point to a prev train
        num_engines--;
        while (CalculateSpeed(current_head) >= min_speed &&
                FindTrainLength(current_head) < max_cars) {
            // loops as long as the train fits the requirements
            if (num_freight > 0) {
                // while there is still freight, check if it can be added,
                // and add it if it can be
                PushBack(current_head, PopFront(f_head));
                num_freight--;
                if (!(CalculateSpeed(current_head) >= min_speed)) {
                    if (FindTrainLength(current_head) < (max_cars * .75)) {
                        PushBack(current_head, PopFront(e_head));
                        num_engines--;
                    } else {
                        PushBack(f_head, PopBack(current_head));
                        num_freight++;
                        break;
                    }
                }
            } else if (num_engines > 0){
                // if there is no more freight, add engines
                PushBack(current_head, PopFront(e_head));
                num_engines--;
            } else { break; }
        }
        if (current_head != NULL) {
            // adds the train
            final_vector.push_back(current_head);
        }
    }
    if (FindTrainLength(f_head) > 0) {
        // makes sure that the head of the freight car doesn't point to a previous train
        f_head->prev = nullptr;
    }
    return final_vector;
}


// separate function responsible for creating two roughly even cars
void Separate(TrainCar* &source, TrainCar* &car1, TrainCar* &car2) {

    // Count the number of engines and non-engine cars in the source list
    car1 = nullptr;
    car2 = nullptr;
    int source_len = FindTrainLength(source);
    int num_engines = CountEngines(source);
    bool on_second = false;

    // Calculate the number of engines and non-engine cars to assign to each list
    int num_engines2 = num_engines / 2;
    int num_engines1 = num_engines - num_engines2;
    int num_1 = (source_len * num_engines1) / num_engines;

    // Traverse the source list and reassign each node's prev and next pointers
    while (source != nullptr) {
        if (!on_second) {
            // makes sure that head doesn't have prev element
            if (FindTrainLength(car1) == 0) {
                source->prev = nullptr;
            }
            // if there is space for more cars, add more cars
            if (num_1 > 0) {
                if (num_1 == 1 && CountEngines(car1) <= 0) {
                    // makes sure that the first train has an engine
                    on_second = true;
                    continue;
                }
                if (num_engines1 > 0 && source->isEngine()) {
                    // if there still needs to be engines added, and the current is an engine it is added
                    num_engines1--;
                    PushBack(car1, PopFront(source));
                    num_1--;
                } else if (num_engines1 <= 0 && source->isEngine()) {
                    // if we hit an engine and dont need it, its given to the second car
                    PushBack(car2, PopFront(source));
                    num_engines2--;
                } else {
                    // adds non engine cars
                    PushBack(car1, PopFront(source));
                    num_1--;
                }

            } else {
                // moves to second car
                on_second = true;
            }
        } else {
            if (num_1 > 0 && source->isEngine()) {
                // if we hit an engine and the first car needs it, we give it to them
                num_1--;
                PushBack(car1, PopFront(source));
                continue;
            }
            if (FindTrainLength(car2) == 0) {
                // adds the rest of the cars
                source->prev = nullptr;
            }
            PushBack(car2, PopFront(source));
        }
    }

    // Set the head pointers of the two new lists
    if (car1 != NULL) {
        car1->prev = NULL;
    }
    if (car2 != NULL) {
        car2->prev = NULL;
    }
}