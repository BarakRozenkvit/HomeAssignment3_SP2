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
    /**
     * use Development card and remove it from _cards or not (if knight or Winpoints so dont)
     * @param card - card name
     */
    void useDevelopmentCard(string card);
    /**
     * check if player has enough resources to pay
     * @param resources
     * @return true or false
     */
    bool canPay(GameSet<Card> &resources);


public:
    Player() {};
    Player(std::string name, int id);
    string getName() { return _name; }
    char getID() { return _id; }
    void addWinningPoints(int amount) { _winPoints += amount; }
    void removeWinningPoints(int amount) { _winPoints -= amount; }
    int getWinPoints() { return _winPoints; }
    void startTurn() {_turnCounter++;_isTurn = true;}
    void endTurn() {_isTurn = false;}
    int getTurn() { return _turnCounter; }
    /**
     * remove from _card the amount of payment
     * @param resources
     */
    void pay(GameSet<Card> &resources);
    /**
     * add to _card the amount of cards
     * @param resources
     * @return
     */
    bool receive(GameSet<Card> &resources);
    /**
     * remove half when size of resources card are more than 7
     * @param set
     */
    void removeHalf(GameSet<ResourceCard>& set);
    /**
     * build property on board at (x,y)
     * @param type
     * @param board
     * @param x
     * @param y
     */
    void build(string type, Board &board, int x, int y);
    /**
     * trade cards with other player
     * @param mySet trade what?
     * @param player with who?
     * @param playerSet with what?
     */
    void trade(GameSet<Card> mySet, Player *player, GameSet<Card> playerSet);
    /**
     * roll the dice, if rand=0 its not random
     * @param rand
     * @return random int
     */
    int rollDice(int rand=0);
    /**
     * buy development card from board and add it
     * @param type
     * @param board
     */
    void buyDevelopmentCard(string type, Board &board);
    /**
     * use WealthyYear card - choose 2 resources to get from board
     * @param resource1
     * @param resource2
     */
    void useWealthyYearCard(string resource1, string resource2);
    /**
     * use Builder Card = choose 2 places to build a road for free
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param board
     */
    void useBuilderCard(int x1, int y1, int x2, int y2, Board& board);
    /**
     * use Monopoly Card - choose a resource to "steal" from other players
     * @param desiredResource
     * @param p
     * @param m
     */
    void useMonopolyCard(string desiredResource, Player *p, Player *m);
    /**
     * use Knight Card - increase your army
     * @return army size
     */
    int useKnightCard();
    /**
     * @return string of player
     */
    string toString();
    /**
     * operator << to player
     * @param out
     * @param p
     * @return Ostream
     */
    friend ostream& operator<<(ostream& out,Player& p){out<<p.toString()<<endl;return out;}
};