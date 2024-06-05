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


