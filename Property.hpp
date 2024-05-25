#include "Card.hpp"
#include <vector>
#include <iostream>
#pragma once

using namespace std;

class Property{
    string _type;
    CardSet _cost;
    int _owner_id;
    int _pointsVal;
    int _amount;

public:
    Property(string type,int amount);

    std::string getType(){return _type;}
    CardSet& getCost(){return _cost;}
    int getPointsValue(){return _pointsVal;}
    int getOwnerID(){return _owner_id;}

    void add(int amount){_amount += amount;}
    void remove(int amount){_amount -= amount;}
    int size(){return _amount;}
    void clear(){_amount=0;}


};

class PropertySet{
    vector<Property> _properties;

public:
    PropertySet();

    Property* search(string type);

    void add(string type,int amount);

    void remove(string type,int amount);

    int size();

    PropertySet& operator-=(Property& property){
        Property* res = search(property.getType());
        res->remove(property.size());
        return *this;
    }

};