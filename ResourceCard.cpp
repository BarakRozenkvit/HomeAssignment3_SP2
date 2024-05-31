#include "ResourceCard.hpp"

bool ResourceCard::operator==(ResourceCard card){
    if(card.getType() == this->getType() && card.size() == this->size()){
        return true;
    }
    return false;
}