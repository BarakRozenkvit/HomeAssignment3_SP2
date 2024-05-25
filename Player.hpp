#include <string>
#include <vector>
#include "Property.hpp"
#include "Card.hpp"
#include "Board.hpp"
#include <iostream>
#pragma once

class Player{
    std::string _name;
    int _id;
    int _winPoints;
    bool _firstTurn = true;
    std::vector<ResourceCard> _resourceCards;
    std::vector<Property> _properties;
    std::vector<DevelopmentCard*> _developmentCard;

public:
    Player(){};
    Player(std::string name,int id): _name(name), _winPoints(2),_id(id){
        _resourceCards = {ResourceCard("Wood"),ResourceCard("Wheat"),
                          ResourceCard("Wool"),ResourceCard("Brick"),
                          ResourceCard("Iron")};
        _properties = {Property("Road",13,_id),
                       Property("Village",3,_id),
                       Property("City",4,_id)};
    };
    ~Player(){}

    string getName(){return _name;}
    int getID(){return _id;}

    bool isFirstTurn(){return _firstTurn;}
    void setFirstTurn(bool boolean){_firstTurn = boolean;}

    bool Buy(Property& property);

    void addWinningPoints(int amount){_winPoints += amount;}
    void removeWinningPoints(int amount){_winPoints -= amount;}

    void removeProperty(Property& property){
        for(int i=0;i<3;i++){
            if(_properties[i].getType() == property.getType()){
                _properties[i].removeAmount(1);
                property.removeAmount(1);
            }
        }
    }

    void addResources(vector<ResourceCard>& resources);
    int removeResource(ResourceCard resource){
        int amount = 0;
        for(int i=0;i<_resourceCards.size();i++){
            if(_resourceCards[i].getResource() == resource.getResource()){
                amount += _resourceCards[i].getAmount();
                _resourceCards[i].clear();
            }
        }
        return amount;
    }

    int getKnights(){
        for(int i=0;i<_developmentCard.size();i++){
            if(_developmentCard[i]->getFeature() == "Knight"){
                return _developmentCard[i]->amountFlashed();
            }
        }
        return 0;
    }

    void addDevelopmentCard(string type);
    DevelopmentCard* useDevelopmentCard(int idx);
    int amountFlashed(string feature);

    void print();
};
