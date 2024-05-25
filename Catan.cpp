#include "Catan.hpp"
#include <iostream>


Catan::Catan(Player* p1, Player* p2, Player* p3) {
    _board = Board();
    _turnsOrder[0] = p1;_turnsOrder[1] = p2;_turnsOrder[2] = p3;
    _developmentCards.add("Development","Knight",4);
    _developmentCards.add("Development","WinningPoints",4);
    _developmentCards.add("Promotion","Monopoly",1);
    _developmentCards.add("Promotion","Builder",1);
    _developmentCards.add("Promotion","WealthyYear",1);
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
    // TODO:check if string valid
    bool res = currentPlayer()->payToBuild(property, currentPlayer()->isFirstTurn());
    if(res){
        return _board.placeProperty(property,currentPlayer()->getID(),true, x, y);
    }
    return false;
}

void Catan::getResources(int rand) {
    vector<ResourceCard> resources;
    if(currentPlayer()->isFirstTurn()) {
        resources = _board.getResources(currentPlayer()->getID(),rand, true);
        currentPlayer()->setFirstTurn(false);
    }
    else{
        resources = _board.getResources(currentPlayer()->getID(),rand, false);
    }
    currentPlayer()->addResources(resources);
}

bool Catan::drawDevelopmentCard(){
    int cardAmount=0;
    for(int i=0;i<_developmentCards.size();i++){
        cardAmount += _developmentCards[i]->getAmount();
    }

    srand(time(0));
    int card_number = (rand() % cardAmount) - 1;

    int counter = 0;
    for(int i=0;i<_developmentCards.size();i++){
        counter += _developmentCards[i]->getAmount();
        if(card_number <= counter) {
            if (_developmentCards[i]->getType() == "Promotion") {
                string benefit = static_cast<PromotionCard *>(_developmentCards[i])->getBenefit();
                currentPlayer()->addDevelopmentCard(benefit);
                return true;
            } else {
                currentPlayer()->addDevelopmentCard(_developmentCards[i]->getFeature());
                return true;
            }
        }
    }
    return false;
}

bool Catan::flashKnight(){
    if(biggestArmy == nullptr && currentPlayer()->amountFlashed("Knight") == 3){
        biggestArmy = currentPlayer();
        maxArmySize = currentPlayer()->amountFlashed("Knight");
        currentPlayer()->addWinningPoints(2);
    }
    else if(biggestArmy != nullptr && maxArmySize < currentPlayer()->amountFlashed("Knight")){
        biggestArmy->removeWinningPoints(2);
        biggestArmy = currentPlayer();
        maxArmySize = currentPlayer()->amountFlashed("Knight");
        currentPlayer()->addWinningPoints(2);
    }
    return true;
}

bool Catan::flashMonopoly(string desiredResource){
    vector<ResourceCard> resource = {ResourceCard(desiredResource)};
    nextPlayer();
    for (int i = 0; i < 2; i++) {
        resource[0].addAmount(currentPlayer()->removeResource(resource[0]));
        nextPlayer();
    }
    currentPlayer()->addResources(resource);
    return true;
}

bool Catan::flashBuilder(int x1,int y1,int x2, int y2){
    Property instance = Property("Road",2,currentPlayer()->getID());
    currentPlayer()->removeProperty(instance);
    _board.placeProperty(instance, false,x1,y1);
    _board.placeProperty(instance, false,x2,y2);
    return true;
}

void Catan::flashWealthyYear(string resource1,string resource2){
    vector<ResourceCard> res;
    if(resource1 == resource2){
        res = {ResourceCard(resource1,2)};
    } else{}
     res = {ResourceCard(resource1),ResourceCard(resource2)};
    currentPlayer()->addResources(res);
}

string Catan::flashDevelopmentCard(int idx){
    DevelopmentCard* getCard = currentPlayer()->useDevelopmentCard(idx);
    if(!getCard){return "";}
    if(getCard->getFeature()=="Promotion"){
        PromotionCard* getCardProm = static_cast<PromotionCard*>(getCard);
        return getCardProm->getBenefit();
    }
    return getCard->getFeature();
}

