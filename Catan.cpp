#include "Catan.hpp"
#include <iostream>


Catan::Catan(Player* p1, Player* p2, Player* p3) {
    _board = Board();
    _turnsOrder[0] = p1;_turnsOrder[1] = p2;_turnsOrder[2] = p3;
    _developmentCards.add("Knight",14);
    _developmentCards.add("WinningPoints",5);
    _developmentCards.add("Monopoly",2);
    _developmentCards.add("Builder",2);
    _developmentCards.add("WealthyYear",1);
}

Player* Catan::nextPlayer(){
    _turnCounter++;
    if(_turnCounter == NUM_OF_PLAYERS){_turnCounter=0;}
    return _turnsOrder[_turnCounter];
}

Player* Catan::currentPlayer() {
    return _turnsOrder[_turnCounter];
}

bool Catan::placeProperty(string property,int x,int y){
    Property temp = Property(property,1);
    // check if can pay
    bool affordable = currentPlayer()->canPay(temp.getCost());
    // check if place is valid
    bool placeValid = _board.canPlaceProperty(temp.getType(),currentPlayer()->getID(),currentPlayer()->isFirstTurn(),x,y);

    if(affordable && placeValid){
        // pay
        currentPlayer()->pay(temp.getCost());
        // build
        currentPlayer()->build(temp);
        // set in graph
        _board.placeProperty(temp.getType(),currentPlayer()->getID(),x,y);
        return true;
    }
    if(!affordable){
        cout << "No Funds" <<endl;
    }
    if(!placeValid){
        cout << "Wrong Place" << endl;
    }
    sleep(2);
    return false;
}

Set<ResourceCard> Catan::getResources(int rand) {
    Set<ResourceCard> resources;
    resources = _board.getResources(currentPlayer()->getID(),currentPlayer()->isFirstTurn(),rand);
    currentPlayer()->setFirstTurn(false);
    currentPlayer()->receive(resources);
    return resources;
}

bool Catan::drawDevelopmentCard(string type){
//    int cardAmount=_developmentCards.total();
//    srand(time(0));
//    int card_number = (rand() % cardAmount);
//    // get Card
//    int j=0;
//    int index;
//    for(int i=0;i<_developmentCards.size();i++){
//        j += _developmentCards.getAt(i).size();
//        if(j >= card_number){
//            index = i;
//            break;
//        }
//    }
    DevelopmentCard card = DevelopmentCard(type,1);
    // Check if Player can Pay
    bool affordable = currentPlayer()->canPay(card.getCost());
    if(affordable){
        // Player Pay
        currentPlayer()->pay(card.getCost());
        // remove from bank
        _developmentCards.remove(card.getType(),1);
        // add to player
        currentPlayer()->addDevelopmentCard(card);
        return true;
    }
    return false;
}

bool Catan::useKnightCard() {
    DevelopmentCard temp = DevelopmentCard("Knight", 1);
    bool res = currentPlayer()->useDevelopmentCard(temp);
    if (res) {
        if (largestArmy == nullptr && currentPlayer()->getArmySize() == 3) {
            largestArmy = currentPlayer();
            currentPlayer()->addWinningPoints(2);
        } else if (largestArmy != nullptr && largestArmy->getArmySize() < currentPlayer()->getArmySize()) {
            largestArmy->removeWinningPoints(2);
            largestArmy = currentPlayer();
            currentPlayer()->addWinningPoints(2);
        }
    }
    return res;
}

bool Catan::useMonopolyCard(string desiredResource) {
    DevelopmentCard temp = DevelopmentCard("Monopoly",1);
    bool res = currentPlayer()->useDevelopmentCard(temp);
    if(res) {
        Set<ResourceCard> wallet;
        Set<ResourceCard> desired;
        desired.add(desiredResource, 1);
        nextPlayer();
        for (int i = 0; i < NUM_OF_PLAYERS; i++) {
            if (currentPlayer()->canPay(desired)) {
                currentPlayer()->pay(desired);
                wallet += desired;
            }
            nextPlayer();
        }
        currentPlayer()->receive(wallet);
    }
    return res;
}

bool Catan::useBuilderCard(int x1, int y1, int x2, int y2) {
    DevelopmentCard temp = DevelopmentCard("Builder",1);
    bool placeValid1 = _board.canPlaceProperty(temp.getType(), currentPlayer()->getID(),
                                               currentPlayer()->isFirstTurn(), x1, y1);
    bool placeValid2 = _board.canPlaceProperty(temp.getType(), currentPlayer()->getID(),
                                               currentPlayer()->isFirstTurn(), x2, y2);
    if (placeValid1 && placeValid2) {
    bool res = currentPlayer()->useDevelopmentCard(temp);
    if(res) {
        Property temp = Property("Road", 1);
        // check if place is valid
            _board.placeProperty(temp.getType(), currentPlayer()->getID(), x1, y1);
            _board.placeProperty(temp.getType(), currentPlayer()->getID(), x2, y2);
            return true;
        }
        return false;
    }
    return false;
}

bool Catan::useWealthyYearCard(string resource1, string resource2) {
    DevelopmentCard temp = DevelopmentCard("WealthyYear",1);
    bool res = currentPlayer()->useDevelopmentCard(temp);
    if(res) {
        Set<ResourceCard> resources;
        resources.add(resource1,1);
        resources.add(resource2,1);
        currentPlayer()->receive(resources);
    }
    return res;
}

bool Catan::checkWin() {
    if(_turnsOrder[0]->getWinPoints() == 10 ||_turnsOrder[1]->getWinPoints() == 10){//|| _turnsOrder[2]->getWinPoints() == 10){
        return true;
    }
    return false;
}


