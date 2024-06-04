#include "Identifiable.hpp"
#include "Countable.hpp"
#pragma once

class ResourceCard  : public Identifiable, public Countable{

public:
    ResourceCard(): Identifiable(), Countable(){};
    ResourceCard(string type,int amount): Identifiable(type), Countable(amount){};
//    bool operator==(ResourceCard card);
};
