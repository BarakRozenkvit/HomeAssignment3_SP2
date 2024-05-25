#include "Card.hpp"

using namespace std;

CardSet::CardSet() {
    _cards = {};
}

void CardSet::add(string type,string name, int amount) {
    Card* result = search(name);
    if(result == nullptr){
        _cards.push_back(Card(type,name,amount));
    }
    result->add(amount);
}

void CardSet::remove(string name, int amount) {
    Card* result = search(name);
    if(result != nullptr){
        result->remove(amount);
    }
}

Card* CardSet::search(string name) {
    for(int i=0;i<_cards.size();i++){
        if(_cards[i].getName() == name){
            return &_cards[i];
        }
    }
    return nullptr;
}

Card* CardSet::getAt(int idx) {
    return &_cards[idx];
}

int CardSet::size() {
    return _cards.size();
}

DevelopmentCard::DevelopmentCard(string name): Card("Development",name,0) {
    _cost.add("Resource", "Iron", 1);
    _cost.add("Resource", "Wool", 1);
    _cost.add("Resource", "Wheat", 1);
}

DevelopmentCard::DevelopmentCard(string name,int amount): Card("Development",name,amount) {
    _cost.add("Resource", "Iron", 1);
    _cost.add("Resource", "Wool", 1);
    _cost.add("Resource", "Wheat", 1);
}


}