#include "Player.hpp"
#include "Set.hpp"
#include <iostream>

Player::Player(string name,int id): _name(name), _winPoints(0),_id(id){
    _resourceCards.add("Wood",0);
    _resourceCards.add("Wheat",0);
    _resourceCards.add("Wool",0);
    _resourceCards.add("Brick",0);
    _resourceCards.add("Iron",0);
    _properties.add("Road",13);
    _properties.add("Village",3);
    _properties.add("City",4);
};

bool Player::payToBuild(string property) {
    int result = _properties.search(property);
    if(result == -1){return false;}
    _winPoints += _properties.getAt(result).getWinPoints();
    if(!_firstTurn){
        _resourceCards -= _properties.getAt(result).getCost();
    }
    _properties.getAt(result).remove(1);
    return true;
}

bool Player::buyDevelopmentCard(string type){
    int result = _developmentCard.search(type);
    if(result == -1){return false;}
    _resourceCards -= _developmentCard.getAt(result).getCost();
    _developmentCard.getAt(result).add(1);
    return true;
}

string Player::flashDevelopmentCard(int index){
    DevelopmentCard& result = _developmentCard.getAt(index);
    result.flashCard();
    if(result.getType() == "")
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

void Player::print() {
    cout << "----------------------------------------------------"<<endl;
    cout<< "name: " <<_name<<endl;
    cout<<"Winning Points: "<<_winPoints<<endl;
    cout<< "ResourceCards: " << _resourceCards << endl;
    cout<< "DevelopmentCards: " << _developmentCard << endl;
    cout << "Properties Left: " << _properties<< endl;
    cout << "----------------------------------------------------"<<endl;

}

