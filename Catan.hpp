#include "Player.hpp"
#include "Board.hpp"
#include "Property.hpp"
#include <iostream>

class Catan {
    Board _board;
    Player* _turnsOrder[3] = {};
    int _turnCounter = -1;

    Set<DevelopmentCard> _developmentCards;

    Player* largestArmy = nullptr;
    Player* longestRoad = nullptr;

public:
    Catan(Player* p1,Player* p2,Player* p3);

    Player* nextPlayer();

    Player* currentPlayer();

    bool placeProperty(string property,int x,int y);

    void getResources(int rand=0);

    bool drawDevelopmentCard();

    bool flashKnight();

    bool flashMonopoly(string desiredResource);

    bool flashBuilder(int x1,int y1,int x2, int y2);

    void flashWealthyYear(string resource1,string resource2);

    string flashDevelopmentCard(int idx);

    bool trade(int id);

    void printGame(){
        cout << _board << endl;
        cout << "Players: " <<endl;
        for(int i=0;i<3;i++){
            cout << _turnsOrder[i] <<endl;
        }

        cout << "Development Cards Bank: "<<endl;
        cout << _developmentCards << endl;
        cout<<endl<<endl;
//        cout << "Largest Army: " << largestArmy<<endl;
//        cout << "Longest Road: "<<longestRoad<<endl;
    }
};