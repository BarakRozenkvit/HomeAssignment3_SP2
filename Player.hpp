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

    bool canPay(Set<ResourceCard>& resources);
    void build(Property& property);
    void buyDevelopmentCard(DevelopmentCard& card);
    bool getResources(Set<ResourceCard>& cardset);

    string useDevelopmentCard(int index);


    bool giveResources(Set<ResourceCard>& set);

    int getArmySize(){
        int card = _developmentCard.search("Knight");
        if(card == -1){return 0;}
        return 0;
    }

    friend ostream& operator<<(ostream& out,Player* p){
        out<< "name: " <<p->_name<<endl;
        out<<"Winning Points: "<<p->_winPoints<<endl;
        out<< "ResourceCards: " << p->_resourceCards << endl;
        out<< "DevelopmentCards: " << p->_developmentCard << endl;
        out << "Properties Left: " << p->_properties<< endl;
        return out;
    }
};
