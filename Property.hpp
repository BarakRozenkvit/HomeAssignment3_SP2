#include "Identifiable.hpp"
#include "Countable.hpp"
#include "Set.hpp"
#include "ResourceCard.hpp"
#include <vector>
#include <iostream>
#pragma once

using namespace std;

class Property: public Countable,public Identifiable{
    int _pointsVal;
    Set<ResourceCard> _cost = Set<ResourceCard>();


public:
    Property(): Countable(), Identifiable(){};
    Property(string type,int amount);
    int getWinPoints(){return _pointsVal;}
    Set<ResourceCard>& getCost(){return _cost;}
//    bool operator==(Property property);
};