#include <string>
#include <vector>
#include "Property.hpp"
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include <iostream>
#pragma once

using namespace std;

class Player{
    string _name;
    char _id;
    int _winPoints;
    bool _firstTurn = true;
    Set<ResourceCard> _resourceCards;
    Set<DevelopmentCard> _developmentCard;
    Set<Property> _properties;

public:
    Player(){};
    Player(std::string name,int id);
    ~Player(){}

    string getName(){return _name;}
    char getID(){return _id;}
    bool isFirstTurn(){return _firstTurn;}
    void setFirstTurn(bool boolean){_firstTurn = boolean;}
    void addWinningPoints(int amount){_winPoints += amount;}
    void removeWinningPoints(int amount){_winPoints -= amount;}

    bool payToBuild(string property);

    bool buyDevelopmentCard(string type);

    string flashDevelopmentCard(int index);

    bool getResources(Set<ResourceCard>& cardset);

    bool giveResources(Set<ResourceCard>& set);

    int getArmySize(){
        int card = _developmentCard.search("Knight");
        if(card == -1){return 0;}
        return 0;
    }

    void print();
};
