#include "Player.hpp"
#include "Set.hpp"
#include "Board.hpp"
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
    if(_turnCounter > 0) {
        if(!canPay(resources)){
            throw invalid_argument("Not Enough Funds");
        }
        _resourceCards -= resources;
    }
}

void Player::build(string type, Board& board, int x, int y) {
    if(!_isTurn && _turnCounter){
        throw invalid_argument("Not his turn!");
    }
    if(_properties.search(type) == -1){
        throw invalid_argument("No Property Exist");
    }
    if(!board.canBuild(type, _id, _turnCounter, x, y)){
        throw invalid_argument("Invalid Place to build");
    }
    Property property = Property(type,1);
    pay(property.getCost());
    board.build(type, _id, x, y);
    _properties.remove(type,1);
    _winPoints += property.getWinPoints();
    if(type == "City"){
        _properties.add("Village",1);
        _winPoints -= Property("Village",1).getWinPoints();
    }
}

void Player::useDevelopmentCard(string type){
    DevelopmentCard card = DevelopmentCard(type,1);
    if(!_isTurn){
        throw invalid_argument("Not his turn!");
    }
    if(_developmentCard.size() == 0){
        throw invalid_argument("Empty Development Cards");
    }
    int res = _developmentCard.search(card.getType());
    if(res == -1){
        throw invalid_argument("Development Card not found");
    }
    DevelopmentCard& result = _developmentCard.getAt(res);
    result.flashCard();
    if(card.getType() == "Monopoly" || card.getType() == "Builder" || card.getType() == "WealthyYear"){
        _developmentCard.remove(card.getType(),card.size());
    }
}

void Player::buyDevelopmentCard(string type, Board &board){
    DevelopmentCard temp = DevelopmentCard(type, 1);
    if (!_isTurn) {
        throw invalid_argument("Not your Turn");
    }
    if (!canPay(temp.getCost())) {
        throw invalid_argument("Not Funds ");
    }
    if (type == "WinningPoints") {
        _winPoints++;
    }

    DevelopmentCard card = board.getDevelopmentCard(temp.getType());
    _developmentCard.add(card.getType(), card.size());
}

void Player::useWealthyYearCard(string resource1, string resource2){
    useDevelopmentCard("WhealthyYear");
    _resourceCards.add(resource1, 1);
    _resourceCards.add(resource2, 1);
    endTurn();
}

void Player::useBuilderCard(int x1, int y1, int x2, int y2, Board board){
    bool placeValid1 = board.canBuild("Road", getID(), _turnCounter, x1, y1);
    bool placeValid2 = board.canBuild("Road", getID(), _turnCounter, x2, y2);
    if (placeValid1 && placeValid2) {
        useDevelopmentCard("Builder");
        build("Road", board, x1, y1);
        build("Road", board, x2, y2);
    }
}

void Player::useMonopolyCard(string desiredResource, Player *p, Player *m){
    if (m == p || m == this || p == this) {
        throw invalid_argument("must include all participants");
    }
    useDevelopmentCard("Monopoly");
    Set<ResourceCard> wallet;
    Set<ResourceCard> desired;
    desired.add(desiredResource, 1);
    if (p->canPay(desired)) {
        p->pay(desired);
        wallet += desired;
    }
    if (m->canPay(desired)) {
        m->pay(desired);
        wallet += desired;
    }
}

int Player::useKnightCard(){
    useDevelopmentCard("Knight");
    int i = _developmentCard.search("Knight");
    return _developmentCard.getAt(i).getAmountFlashed();
}

void Player::getResources(Board& board,int rand){
    Set<ResourceCard> res = board.getResources(_id,_turnCounter,rand);
    receive(res);
}

bool Player::receive(Set<ResourceCard>& resources) {
    _resourceCards += resources;
    return true;
}

void Player::removeHalf(Set<ResourceCard> set) {
    if (_resourceCards.total() < 7) {
        throw invalid_argument("Cant reduce resources");
    }
    if (!canPay(set)) {
        throw invalid_argument("Cant Pay resources");
    }
    pay(set);
}

void Player::trade(Set<ResourceCard> mySet, Player *player, Set<ResourceCard> playerSet) {
    if (player == this) {
        throw invalid_argument("Cant trade with yourself");
    }
    if (!_isTurn) {
        throw invalid_argument("Not my turn");
    }
    if (canPay(mySet) && player->canPay(playerSet)) {
        pay(mySet);
        player->pay(playerSet);
        receive(playerSet);
        player->receive(mySet);
    } else {
        throw invalid_argument("Invalid Trade");
    }
}


