// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
#ifndef _ds_traincar_prototypes_
#define _ds_traincar_prototypes_
#include "traincar.h"
#include <iostream>
#include <fstream>
#include <vector>

// adds a new node to the end of the train
void PushBack(TrainCar* &head, TrainCar* car_to_add);

// deallocates all the memory of a train
void DeleteAllCars(TrainCar* &head);

// calculates the speed of a given train
float CalculateSpeed(TrainCar* &head);

// bulk of our statistic calculations
void TotalWeightAndCountCars(TrainCar* &head, int &total_weight, int &num_engines,
        int &num_freight, int &num_passenger, int &num_dining, int &num_sleeping);

// calculates the avg distance from passenger cars to dining cars
float AverageDistanceToDiningCar(TrainCar* &head);

// finds the closest engine piece to a sleeper car
int ClosestEngineToSleeperCar(TrainCar* &head);

// ship freight function that splits freight up among a vector of trains
std::vector<TrainCar*> ShipFreight(TrainCar* &e_head, TrainCar* &f_head,
                                   int min_speed, int max_cars);

// finds the integer length of a given train
int FindTrainLength(TrainCar* &head);

// removes the front element of a list, returning the node
TrainCar* PopFront(TrainCar* &head);

// removes the back element of a list, returning the node
TrainCar* PopBack(TrainCar* &head);

// counts the number of engines in a given train
int CountEngines(TrainCar* &head);

// separate function responsible for creating two roughly even cars
void Separate(TrainCar* &source, TrainCar* &car1, TrainCar* &car2);

#endif // _ds_traincar_prototypes_