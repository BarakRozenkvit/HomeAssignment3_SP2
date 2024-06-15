#include "Land.hpp"
#include "Graph.hpp"
#include "Card.hpp"
#include <stdexcept>
#pragma once

using namespace std;

class Board{
    Graph _graph;
    Land _lands[19];
    GameSet<DevelopmentCard> _developmentCards;
    /**
     * Creating the Lands,  defining each land where it belongs on board and assigning each land a number
     */
    void init();

public:
    Board(){init();}
    /**
     * Check if Player can build on specific (x,y)
     * @param property - string of property type
     * @param id - id of player
     * @param turnCounter - turn number of player
     * @param x
     * @param y
     * @return true or false
     */
    bool canBuild(string property, char id, int turnCounter, int x, int y);
    /**
     * place property on board
     * @param property - string of property type
     * @param id - id of player
     * @param x
     * @param y
     */
    void build(string property, char id, int x, int y);
    /**
     * get Resource from properties built on board
     * @param id - id of player
     * @param turnCounter - turn number of player
     * @param rand - dice number
     * @return
     */
    GameSet<ResourceCard> getResources(char id, int turnCounter, int rand);
    /**
     * get Development card from stack of board
     * @param type - name of card
     * @return Development Card Instance
     */
    DevelopmentCard getDevelopmentCard(string type);
};
