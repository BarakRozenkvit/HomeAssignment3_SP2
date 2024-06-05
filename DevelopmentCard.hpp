#include "Identifiable.hpp"
#include "Countable.hpp"
#include "Set.hpp"
#include "ResourceCard.hpp"
#pragma once

class DevelopmentCard: public Identifiable,public Countable{
    Set<ResourceCard> _cost;
    int _flashedAmount;
    int _turnNum;

public:
    DevelopmentCard(string type,int amount,int turnNumber=-1): Countable(amount),Identifiable(type){
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
