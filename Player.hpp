//314638669 | Barak10101998@gmail.com
#include <iostream>
#include "Card.hpp"
#include "Property.hpp"
#include "Board.hpp"
#include "Dice.hpp"
#include "GameSet.hpp"
#pragma once

using namespace std;

class Player {
    string _name;
    char _id;
    int _winPoints;
    int _turnCounter;
    bool _isTurn;
    int _armySize;
    GameSet<Card> _cards;
    GameSet<Property> _properties;

    void useDevelopmentCard(string card);
    bool canPay(GameSet<Card> &resources);


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
    void endTurn() {_isTurn = false;}
    int getTurn() { return _turnCounter; }
    void pay(GameSet<Card> &resources);
    bool receive(GameSet<Card> &resources);
    void removeHalf(GameSet<ResourceCard>& set);
    void build(string type, Board &board, int x, int y);
    void trade(GameSet<Card> mySet, Player *player, GameSet<Card> playerSet);
    int rollDice(int rand=0);
    void buyDevelopmentCard(string type, Board &board);
    void useWealthyYearCard(string resource1, string resource2);
    void useBuilderCard(int x1, int y1, int x2, int y2, Board& board);
    void useMonopolyCard(string desiredResource, Player *p, Player *m);
    int useKnightCard();
    string toString();
    friend ostream& operator<<(ostream& out,Player* p){out<<p->toString()<<endl;return out;}
};