#include "Player.hpp"
#include "Set.hpp"
#include <iostream>

Player::Player(string name,int id): _name(name), _winPoints(0),_id(id){
    _properties.add("Road",15);
    _properties.add("Village",5);
    _properties.add("City",4);
};

bool Player::canPay(Set<ResourceCard> &resources) {
    if(_firstTurn){return true;}
    return _resourceCards > resources;
}

void Player::pay(Set<ResourceCard> &resources){
    if(!_firstTurn) {
        _resourceCards -= resources;
    }
}

void Player::build(Property &property) {
    _properties.remove(property.getType(),property.size());
    _winPoints += property.getWinPoints();
}

void Player::addDevelopmentCard(DevelopmentCard& card){
    if(card.getType() == "WinningPoints"){
        _winPoints++;
    }
    _developmentCard.add(card.getType(), card.size());
}

bool Player::useDevelopmentCard(DevelopmentCard& card){
    if(_developmentCard.size() == 0){
        return false;
    }
    int res = _developmentCard.search(card.getType());
    if(res == -1){
        return false;
    }

    DevelopmentCard& result = _developmentCard.getAt(res);
    result.flashCard();
    if(card.getType() == "Monopoly" || card.getType() == "Builder" || card.getType() == "WealthyYear"){
        _developmentCard.remove(card.getType(),card.size());
    }
    return true;
}

bool Player::receive(Set<ResourceCard>& resources) {
    _resourceCards += resources;
    return true;
}

int Player::getArmySize(){
    int card = _developmentCard.search("Knight");
    if(card == -1){return 0;}
    return _developmentCard.getAt(card).getAmountFlashed();

}


