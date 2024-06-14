#include "Land.hpp"
#include "Graph.hpp"
#include "Property.hpp"
#include "Card.hpp"
#pragma once

using namespace std;

class Board{
    Graph _graph;
    Land _lands[19];
    GameSet<DevelopmentCard> _developmentCards;

    void init();

public:
    Board(){init();}

    bool canBuild(string property, char id, int turnCounter, int x, int y);

    void build(string property, char id, int x, int y);

    GameSet<ResourceCard> getResources(char id, int turnCounter, int rand);

    DevelopmentCard getDevelopmentCard(string type);
};
