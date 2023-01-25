#ifndef __animal_h__
#define __animal_h__
#include <iostream>
#include <string>

class Animal {

    public:
        // public vars
        // these are public bc the document says they must be accessed from outside the class
        std::string name;
        int weight;
        bool waterType;
        bool groundType;
        bool carnivorous;
        bool herbivorous;

        // constructors
        Animal();
        // takes in a string aname and sets name to that
        Animal(std::string aname);

        // setters

        // sets weight
        void setWeight(int aweight);
        // sets whether or not the animal can live in the water
        void setWaterType(bool iswatertype);
        // sets whether or not the animal can live on the ground
        void setGroundType(bool isgroundtype);
        // sets whether or not the animal can eat meat
        void setCarnivorous(bool iscarnivorous);
        // sets whether or not the animal can eat plants
        void setHerbivorous(bool isherbivorous);
        // returns a bool value of whether or not the animal can eat both meat and plants
        bool isOmnivorous();
        // returns a bool value of whether or not the animal can live in both water and air
        bool isAmphibious();


};
#endif