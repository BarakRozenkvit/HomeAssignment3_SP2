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
    int index;
    srand(time(0));
    int card_number = (rand() % cardAmount) - 1;
    int counter = 0;
    for(int i=0;i<_developmentCards.size();i++){
        counter += _developmentCards.getAt(i).size();
        if(card_number <= counter) {
            int index = i;
            break;
        }
    }
    bool res = currentPlayer()->buyDevelopmentCard(_developmentCards.getAt(index).getType(),_developmentCards.getAt(index).getCost());
    if(res){
        cout << "Bought!" <<endl;
        return true;
    }
    else{
        cout << "Not enogh funds" << endl;
        return false;
    }
}

bool Catan::flashKnight(){
    if(largestArmy == nullptr && currentPlayer()->getArmySize() == 3){
        largestArmy = currentPlayer();
        currentPlayer()->addWinningPoints(2);
    }
    else if(largestArmy != nullptr && largestArmy->getArmySize() < currentPlayer()->getArmySize()){
        largestArmy->removeWinningPoints(2);
        largestArmy = currentPlayer();
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

bool Catan::useDevelopmentCard(int idx){
    string res = currentPlayer()->useDevelopmentCard(idx);
    if(res == "empty"){
        return false;
    }
    if (res == "Knight") {
        flashKnight();
        return true;
    }
    else if (res == "Monopoly") {
        string desired_resource;
        cout << "Choose desired resource which you take from others: " << endl;
        cin >> desired_resource;
        flashMonopoly(desired_resource);
        return true;
    }
    else if (res == "Builder") {
        int x1, x2, y1, y2;
        std::cout << "Choose Where to place the 1st Road" << endl;
        std::cin >> x1 >> y1;
        std::cout << "Choose Where to place the 2st Road" << endl;
        std::cin >> x2 >> y2;
        flashBuilder(x1, y1, x2, y2);
        return true;
    }
    else if (res == "WealthyYear") {
        string resource1, resource2;
        std::cout << "Choose 2 Resource to take from Bank (can be the same)" << endl;
        cin >> resource1 >> resource2;
        flashWealthyYear(resource1, resource2);
        return true;
    }
    else{
        return false;
    }
}

