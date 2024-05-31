#include "Catan.hpp"
#include <iostream>


Catan::Catan(Player* p1, Player* p2, Player* p3) {
    _board = Board();
    _turnsOrder[0] = p1;_turnsOrder[1] = p2;_turnsOrder[2] = p3;
    _developmentCards.add("Knight",4);
    _developmentCards.add("WinningPoints",4);
    _developmentCards.add("Monopoly",1);
    _developmentCards.add("Builder",1);
    _developmentCards.add("WealthyYear",1);
}

Player* Catan::nextPlayer(){
    _turnCounter++;
    if(_turnCounter == 3){_turnCounter=0;}
    return _turnsOrder[_turnCounter];
}

Player* Catan::currentPlayer() {
    return _turnsOrder[_turnCounter];
}

bool Catan::placeProperty(string property,int x,int y){
    bool res = currentPlayer()->payToBuild(property);
    if(res){
        return _board.placeProperty(property,currentPlayer()->getID(),currentPlayer()->isFirstTurn(), x, y);
    }
    return false;
}

void Catan::getResources(int rand) {
    Set<ResourceCard> resources;
    resources = _board.getResources(currentPlayer()->getID(),currentPlayer()->isFirstTurn(),rand);
    currentPlayer()->setFirstTurn(false);
    currentPlayer()->getResources(resources);
}

bool Catan::drawDevelopmentCard(){
    int cardAmount=0;
    for(int i=0;i<_developmentCards.size();i++){
        cardAmount += _developmentCards.getAt(i).size();
    }

    srand(time(0));
    int card_number = (rand() % cardAmount) - 1;
    int counter = 0;
    for(int i=0;i<_developmentCards.size();i++){
        counter += _developmentCards.getAt(i).size();
        if(card_number <= counter) {
            currentPlayer()->buyDevelopmentCard(_developmentCards.getAt(i).getType());
            return true;
        }
    }
    return false;
}

bool Catan::flashKnight(){
    if(biggestArmy == nullptr && currentPlayer()->getArmySize() == 3){
        biggestArmy = currentPlayer();
        currentPlayer()->addWinningPoints(2);
    }
    else if(biggestArmy != nullptr && biggestArmy->getArmySize() < currentPlayer()->getArmySize()){
        biggestArmy->removeWinningPoints(2);
        biggestArmy = currentPlayer();
        currentPlayer()->addWinningPoints(2);
    }
    return true;
}

bool Catan::flashMonopoly(string desiredResource){
    Set<ResourceCard> resource;
    resource.add(desiredResource,1);
    bool amount;
    nextPlayer();
    for (int i = 0; i < 2; i++) {
        bool res = currentPlayer()->giveResources(resource);
        if(res){resource += resource;}
        nextPlayer();
    }
    currentPlayer()->getResources(resource);
    return true;
}

bool Catan::flashBuilder(int x1,int y1,int x2, int y2){
    placeProperty("Road",x1,y1);
    placeProperty("Road",x2,y2);
    return true;
}

void Catan::flashWealthyYear(string resource1,string resource2){
    Set<ResourceCard> res;
    res.add(resource1,1);
    res.add(resource2,1);
    currentPlayer()->getResources(res);
}

string Catan::flashDevelopmentCard(int idx){
    return currentPlayer()->flashDevelopmentCard(idx);
}

