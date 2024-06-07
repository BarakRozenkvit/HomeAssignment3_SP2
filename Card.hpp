#include "Identifiable.hpp"
#include "Countable.hpp"
#include "Set.hpp"
#pragma once

class Card  : public Identifiable, public Countable{
public:
    Card(): Identifiable(), Countable(){};
    Card(string type,int amount): Identifiable(type), Countable(amount){};
};

class ResourceCard : public Card{
public:
    ResourceCard(): Card(){};
    ResourceCard(string type,int amount): Card(type,amount){};
};


class DevelopmentCard: public Card{
    Set<ResourceCard> _cost;
    int _flashedAmount;
    int _turnNum;

public:
    DevelopmentCard(string type,int amount,int turnNumber=-1): Card(type,amount){
        _cost.add("Iron",1);
        _cost.add("Wool",1);
        _cost.add("Wheat",1);
        _flashedAmount = 0;
        _turnNum = turnNumber;
    };

    Set<ResourceCard>& getCost(){return _cost;}
    void flashCard(){_flashedAmount++;}
    int getAmountFlashed(){return _flashedAmount;}



};
