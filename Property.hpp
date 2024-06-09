#include "Identifiable.hpp"
#include "Countable.hpp"
#include "GameSet.hpp"
#include "Card.hpp"
#include <vector>
#include <iostream>
#pragma once

using namespace std;

class Property: public Countable,public Identifiable{
    int _pointsVal;
    GameSet<ResourceCard> _cost = GameSet<ResourceCard>();


public:
    Property(): Countable(), Identifiable(){};
    Property(string type,int amount);
    int getWinPoints(){return _pointsVal;}
    GameSet<ResourceCard>& getCost(){return _cost;}
};