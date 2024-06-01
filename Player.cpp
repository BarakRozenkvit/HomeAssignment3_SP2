#include "Player.hpp"
#include "Set.hpp"
#include <iostream>

Player::Player(string name,int id): _name(name), _winPoints(0),_id(id){
    _resourceCards.add("Wood",0);
    _resourceCards.add("Wheat",0);
    _resourceCards.add("Wool",0);
    _resourceCards.add("Brick",0);
    _resourceCards.add("Iron",0);
    _properties.add("Road",15);
    _properties.add("Village",5);
    _properties.add("City",4);
};

bool Player::canPay(Set<ResourceCard> &resources) {
    if(_firstTurn){return true;}
    return _resourceCards > resources;
}

void Player::build(Property &property) {
    _properties.remove(property.getType(),property.size());
    _resourceCards -= property.getCost();
    _winPoints += property.getWinPoints();
}

void Player::buyDevelopmentCard(DevelopmentCard& card){
    _resourceCards -= card.getCost();
    _developmentCard.add(card.getType(),card.size());
}

string Player::useDevelopmentCard(int index){
    if(_developmentCard.size() == 0){
        cout << "Development Cards are empty!" << endl;
        return "empty";
    }
    DevelopmentCard& result = _developmentCard.getAt(index);
    cout << "Requested " << result.getType() << endl;
    result.flashCard();
    return result.getType();
}

bool Player::getResources(Set<ResourceCard>& set) {
    _resourceCards += set;
    return true;
}

bool Player::giveResources(Set<ResourceCard>& set) {
    _resourceCards -= set;
    return true;
}


