#include "Player.hpp"
#include "Board.hpp"
#include "Property.hpp"
#include <iostream>
#include <unistd.h>
#define NUM_OF_PLAYERS 3

class Catan {
    Board _board;
    Player* _turnsOrder[NUM_OF_PLAYERS] = {};
    int _turnCounter = -1;

    Player* largestArmy = nullptr;
    int _largestArmySize = 0;
    Player* longestRoad = nullptr;

public:
    Catan(){};
    Catan(Player* p1,Player* p2,Player* p3);

    Board& getBoard(){return _board;}

    bool checkWin();

    void checkLargestArmy(Player* p,int n){
        if (largestArmy == nullptr && n == 3) {
            largestArmy = p;
            p->addWinningPoints(2);
        } else if (largestArmy != nullptr && _largestArmySize < n) {
            largestArmy->removeWinningPoints(2);
            largestArmy = p;
            p->addWinningPoints(2);
        }
    }
};