#include "Identifiable.hpp"
#include "Countable.hpp"
#include "GameSet.hpp"
#pragma once

class Card  : public Identifiable, public Countable{

public:
    Card(): Identifiable(), Countable(){};
    Card(string type,int amount): Identifiable(type), Countable(amount) {};
};

class ResourceCard : public Card{
public:
    ResourceCard(): Card(){};
    ResourceCard(string type,int amount): Card(type,amount){
        bool resource = type == "Wool" || type == "Wood" || type == "Wheat" || type == "Iron" || type == "Brick";
        if(!resource){
            throw invalid_argument("No card in this game");
        }
    };
};


class DevelopmentCard: public Card{
    GameSet<ResourceCard> _cost;
    int _flashedAmount;
    int _turnNum;

public:
    DevelopmentCard(string type,int amount,int turnNumber=-1): Card(type,amount){
        bool development = type == "Knight" || type == "WinningPoints" || type == "Monopoly" || type == "Builder" ||
                           type == "WealthyYear";
        if(!development) {
            throw invalid_argument("No card in this game");
        }
        _cost.add("Iron",1);
        _cost.add("Wool",1);
        _cost.add("Wheat",1);
        _flashedAmount = 0;
        _turnNum = turnNumber;
    };

    GameSet<ResourceCard>& getCost(){return _cost;}
    void flashCard(){_flashedAmount++;}
    int getAmountFlashed(){return _flashedAmount;}



};
