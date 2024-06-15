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
    ResourceCard(string type,int amount);
};

class DevelopmentCard: public Card{
    GameSet<ResourceCard> _cost;

public:
    DevelopmentCard(string type,int amount);

    GameSet<ResourceCard>& getCost(){return _cost;}
};
