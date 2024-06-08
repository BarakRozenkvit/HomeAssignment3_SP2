/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;

int main() {
    Player *Omri = new Player("Omri", 10);
    Player *Barak = new Player("Barak", 20);
    Player *Haim = new Player("Haim", 30);
    Catan catan(Omri, Barak, Haim);
    // Starting of the game. Every player places two settlements and two roads.
//    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board& board = catan.getBoard(); // get the board of the game.

    Omri->build("Village", board, 23, 23);
    Omri->build("Road", board, 23, 29);
    Omri->build("Village", board, 14, 14);
    Omri->build("Road", board, 14, 9);

    Barak->build("Village", board, 45, 45);
    Barak->build("Road", board, 45, 41);
    Barak->build("Village", board, 22, 22);
    Barak->build("Road", board, 41, 36);

    Haim->build("Village", board, 39, 39);
    Haim->build("Road", board, 39, 43);
    Haim->build("Village", board, 47, 47);
    Haim->build("Road", board, 47, 43);

    catan.distributeResources();
    //Omri: Wood 1 Wheat 1 Wool 2 Iron 2
    //Barak: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 1
    //Haim: Brick 1 Wheat 1 Wood 2




    Omri->startTurn();
    int rand = Omri->rollDice(8);
    catan.distributeResources(rand);
    // Omri got nothing: Wood 1 Wheat 1 Wool 2 Iron 2
    // Barak got Wool 1: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    // Haim got Brick 1: Brick 2 Wheat 1 Wood 2

    Omri->buyDevelopmentCard("WinningPoints", board);
    // Omri got 3 winPoints: Wood 1 Wool 1 Iron 1
    Omri->endTurn();

    Barak->startTurn();
    rand = Barak->rollDice(9);
    catan.distributeResources(rand);
    // Omri got Wool 1: Wood 1 Wool 2 Iron 1
    // Barak got nothing: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    // Haim got nothing: Brick 2 Wheat 1 Wood 2

    Barak->build("Road", board, 22, 28);
    // Barak: Iron 1 Wheat 2 Wool 2
    Set<Card> barakTrade;
    barakTrade.add("Iron", 1);
    Set<Card> omriSet;
    omriSet.add("Wool", 1);
    Barak->trade(barakTrade, Omri, omriSet);
    // Barak: Wheat 2 Wool 3
    // Omri: Wood 1 Wool 1 Iron 2
    Barak->endTurn();

    Haim->startTurn();
    rand = Haim->rollDice(7);
    // Omri, Haim and Barak don't have more than 7 cards

    Set<Card> haimSet;
    haimSet.add("Wood", 2);
    omriSet.clear();
    omriSet.add("Iron", 1);
    Haim->trade(haimSet, Omri, omriSet);
    // Haim: Brick 2 Wheat 1 Iron 1
    // Omri: Wood 3 Wool 1 Iron 1
    Haim->endTurn();

    Omri->startTurn();
    rand= Omri->rollDice(11);
    catan.distributeResources(rand);
    // Omri got Wood 1: Wood 4 Wool 1 Iron 1
    // Barak got Wood 1: Wood 1 Wheat 2 Wool 3
    // Haim got nothing: Brick 2 Wheat 1 Iron 1
    Set<Card> omriTrade;omriTrade.add("Wood",1);
    Set<Card> haimTrade;haimTrade.add("Wheat",1);haimTrade.add("Brick",1);
    Omri->trade(omriTrade,Haim,haimTrade);
    // Omri: Wood 3 Wool 1 Iron 1 Wheat 1 Brick 1
    // Hami: Brick 1 Iron 1 Wood 1
    Omri->build("Road",board,29,35);
    // Omri: Wood 2 Wool 1 Iron 1 Wheat 1

    Omri->endTurn();

    Barak->startTurn();
    rand = Barak->rollDice(5);
    catan.distributeResources(rand);
    // Omri got Iron 1: Wood 2 Wool 1 Iron 2 Wheat 1
    // Barak got nothing: Wood 1 Wheat 2 Wool 3
    // Haim got nothing: Brick 1 Iron 1 Wood 1

    omriTrade.clear();omriTrade.add("Iron",1);
    barakTrade.clear();barakTrade.add("Wheat",1);
    Barak->trade(barakTrade,Omri,omriTrade);
    //Barak: Wood 1 Wheat 1 Wool 3 Iron 1
    // Omri: Wood 2 Wool 1 Iron 1 Wheat 2
    Barak->buyDevelopmentCard("Monopoly",board);
    // Barak: Wood 1 Wool 2
    Barak-> endTurn();

    Haim->startTurn();
    rand=Haim->rollDice(8);
    catan.distributeResources(rand);
    // Omri got Iron 1: Wood 2 Wool 1 Iron 1 Wheat 2
    // Barak got Wool 1: Wood 1 Wool 3
    // Haim got Brick 1: Brick 2 Iron 1 Wood 1
    Haim->build("Road",board,38,43);
    // Haim: Brick 1 Iron 1
    Haim->endTurn();

    Omri->startTurn();
    rand=Omri->rollDice(5);
    catan.distributeResources(rand);
    // Omri got Iron 1: Wood 2 Wool 1 Iron 2 Wheat 2
    // Barak got got nothing: Wood 1 Wool 3
    // Haim got nothing: Brick 1 Iron 1
    Omri->buyDevelopmentCard("Builder",board);
    // Omri: Wood 2 Iron 1 Wheat 1
    Omri->endTurn();

    Barak->startTurn();
    Barak->useMonopolyCard("Brick",Omri,Haim);
    // Barak: Wood 1 Wool 3 Brick 1
    // Haim: Iron 1
    // Omri: Wood 2 Iron 1 Wheat 1

    Haim->startTurn();
    rand=Haim->rollDice(8);
    catan.distributeResources(rand);
    // Omri got Iron 1: Wood 2 Iron 1 Wheat 1
    // Barak got Wool 1: Wood 1 Wool 4 Brick 1
    // Haim got nothing: Brick 1 Iron 1
    Haim->endTurn();

    Omri->startTurn();
    rand=Omri->rollDice(2);
    catan.distributeResources(rand);
    // Omri got Iron 1: Wood 2 Iron 2 Wheat 1
    // Barak got nothing : Wood 1 Wool 4 Brick 1
    // Haim got nothing: Brick 1 Iron 1
    Omri->useBuilderCard(9,13,35,40,board);
}