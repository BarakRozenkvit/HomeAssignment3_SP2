//314638669 | Barak10101998@gmail.com
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

public:
    DevelopmentCard(string type,int amount): Card(type,amount){
        bool development = type == "Knight" || type == "WinningPoints" || type == "Monopoly" || type == "Builder" ||
                           type == "WealthyYear";
        if(!development) {
            throw invalid_argument("No card in this game");
        }
        _cost.add("Iron",1);
        _cost.add("Wool",1);
        _cost.add("Wheat",1);
    };

    GameSet<ResourceCard>& getCost(){return _cost;}
};
