#include "Catan.hpp"
#include <iostream>


Catan::Catan(Player* p1, Player* p2, Player* p3) {
    _board = Board();
    _turnsOrder[0] = p1;_turnsOrder[1] = p2;_turnsOrder[2] = p3;
}

bool Catan::checkWin() {
    if(_turnsOrder[0]->getWinPoints() == 10 ||_turnsOrder[1]->getWinPoints() == 10){//|| _turnsOrder[2]->getWinPoints() == 10){
        return true;
    }
    return false;
}

void Catan::distributeResources(int rand) {
    for (int i = 0; i < 3; i++) {
        Player *p = _turnsOrder[i];
        GameSet<ResourceCard> res = _board.getResources(p->getID(), p->getTurn(), rand);
        GameSet<Card> resToCard = (GameSet<Card>)res;
        if(p->getTurn() == 0){p->startTurn();p->endTurn();}
        p->receive(resToCard);
        if(res.size() == 0){
            cout << p->getName() << " Got nothing"<<endl;
        }
        else {
            cout << p->getName() << " Got :" << res << endl;
        }
    }
}