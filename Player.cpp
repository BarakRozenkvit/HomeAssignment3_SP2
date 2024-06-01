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

bool Player::payToBuild(string property) {
    int result = _properties.search(property);
    if(result == -1){return false;}
    _winPoints += _properties.getAt(result).getWinPoints();
    if(!_firstTurn){
        if(_properties.getAt(result).getCost() > _resourceCards){
            cout << "Not enoght funds!" << endl;
            return false;
        }
        _resourceCards -= _properties.getAt(result).getCost();
    }
    _properties.getAt(result).remove(1);
    return true;
}

bool Player::buyDevelopmentCard(string type,Set<ResourceCard>& cost){
    if(cost > _resourceCards){return false;}
    _resourceCards -= cost;
    _developmentCard.add(type,1);
    return true;
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


