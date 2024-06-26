//314638669 | Barak10101998@gmail.com
#include "Player.hpp"
#include "Board.hpp"
#include <unistd.h>

class Catan {
    Board _board;
    Player* _turnsOrder[3] = {};
    Player* largestArmy = nullptr;
    int _largestArmySize = 0;

public:
    Catan(){};
    Catan(Player* p1,Player* p2,Player* p3);

    Board& getBoard(){return _board;}
    /**
     * Iterate through all players and give resources
     * @param rand - random number, default is zero
     */
    void distributeResources(int rand=0);

    string printWinner();
    /**
     * Check current player if has the largest army and assign him
     * @param p - current player to check
     * @param n - size of the player's army
     */
    void checkLargestArmy(Player* p,int n){
        if (largestArmy == nullptr && n == 3) {
            largestArmy = p;
            _largestArmySize = n;
            p->addWinningPoints(2);
        } else if (largestArmy != nullptr && _largestArmySize < n) {
            largestArmy->removeWinningPoints(2);
            largestArmy = p;
            _largestArmySize = n;
            p->addWinningPoints(2);
        }
    }

    Player* getLargestArmy(){
        return largestArmy;
    }
};