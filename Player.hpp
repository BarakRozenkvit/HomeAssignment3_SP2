#include <iostream>
#include "Card.hpp"
#include "Property.hpp"
#include "Board.hpp"
#include "Dice.hpp"
#include "Set.hpp"
#pragma once

using namespace std;

class Player {
    string _name;
    char _id;
    int _winPoints;
    int _turnCounter = 0;
    bool _isTurn;
    string _currentUseDevelopment;
//    bool _firstTurn = true;
//    Set<ResourceCard> _resourceCards;
//    Set<DevelopmentCard> _developmentCard;
    Set<Card> _cards;
    Set<Property> _properties;
    void useDevelopmentCard(string card);


public:
    Player() {};

    Player(std::string name, int id);

    ~Player() {}

    string getName() { return _name; }

    char getID() { return _id; }

    void addWinningPoints(int amount) { _winPoints += amount; }

    void removeWinningPoints(int amount) { _winPoints -= amount; }

    int getWinPoints() { return _winPoints; }

    void startTurn() {_turnCounter++;_isTurn = true;}

    void endTurn() {_isTurn = false; }

    int getTurn() { return _turnCounter; }

    bool canPay(Set<Card> &resources);

    void pay(Set<Card> &resources);

    bool receive(Set<Card> &resources);

    void removeHalf(Set<ResourceCard> set);

    void build(string type, Board &board, int x, int y);

    void trade(Set<Card> mySet, Player *player, Set<Card> playerSet);

    void buyDevelopmentCard(string type, Board &board);

    int rollDice(int rand=0) {
        if(!_isTurn){throw invalid_argument("not his turn");}
        if(rand){
            return rand;
        }
        return Dice::roll();}

    void useWealthyYearCard(string resource1, string resource2);

    void useBuilderCard(int x1, int y1, int x2, int y2, Board& board);

    void useMonopolyCard(string desiredResource, Player *p, Player *m);

    int useKnightCard();

    void getResources(Board& board,int rand=0);

    friend ostream &operator<<(ostream &out, Player* p) {
        out << "name: " << p->_name << endl;
        out << "Winning Points: " << p->_winPoints << endl;
        out << "Cards: " << p->_cards << endl;
//        out << "Properties Left: " << p->_properties << endl;
        return out;
    }
};