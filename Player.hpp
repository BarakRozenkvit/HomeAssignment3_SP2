#include <string>
#include <vector>
#include "Property.hpp"
#include "Card.hpp"
#include "Board.hpp"
#include <iostream>
#pragma once

using namespace std;

class Player{
    std::string _name;
    int _id;
    int _winPoints;
    bool _firstTurn = true;
    CardSet _resourceCards;
    CardSet _developmentCard;
    PropertySet _properties;

public:
    Player(){};
    Player(std::string name,int id);
    ~Player(){}

    string getName(){return _name;}
    int getID(){return _id;}
    bool isFirstTurn(){return _firstTurn;}
    void setFirstTurn(bool boolean){_firstTurn = boolean;}
    void addWinningPoints(int amount){_winPoints += amount;}
    void removeWinningPoints(int amount){_winPoints -= amount;}

    bool payToBuild(string property,bool firstTurn);

    bool buyDevelopmentCard(string type="Development",string name="");

    bool flashDevelopmentCard(string name="");

    bool getResources();

    bool giveResources();

//    void print();
};
