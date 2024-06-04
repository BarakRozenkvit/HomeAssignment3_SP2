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

    Set<DevelopmentCard> _developmentCards;

    Player* largestArmy = nullptr;
    Player* longestRoad = nullptr;

public:
    Catan(Player* p1,Player* p2,Player* p3);

    Player* nextPlayer();

    Player* currentPlayer();

    bool placeProperty(string property,int x,int y);

    Set<ResourceCard> getResources(int rand=0);

    bool drawDevelopmentCard(string type);

    bool useKnightCard();

    bool useMonopolyCard(string desiredResource);

    bool useBuilderCard(int x1,int y1,int x2, int y2);

    bool useWealthyYearCard(string resource1,string resource2);

    void printGame(string option,Player* p=nullptr){
        system("clear");
        cout << _board << endl;
        cout << "Devolopment Cards Cost: " << _developmentCards.getAt(0).getCost() << endl;
        cout << "Road Cost: " <<Property("Road",1).getCost() << endl;
        cout << "Village Cost: " <<Property("Village",1).getCost() << endl;
        cout << "City Cost: " <<Property("City",1).getCost() << endl;
        if(largestArmy == nullptr){
            cout << "Largest Army: None"<<endl;
        } else{ cout << "Largest Army: " << largestArmy<<endl;}
        if(longestRoad == nullptr){
            cout << "Longest Road: None"<<endl;
        } else{ cout << "Longest Road: " << longestRoad<<endl;}
        cout << "-------------------------------------------------" <<endl;
        if(p== nullptr){
            cout << currentPlayer() <<endl;
        }
        else{
            cout << p <<endl;
        }
        cout << option <<endl;
    }

    bool checkWin();
};