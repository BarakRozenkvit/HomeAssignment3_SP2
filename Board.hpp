#include "Hexagon.hpp"
#include "Land.hpp"
#include "Graph.hpp"
#include "Property.hpp"
#pragma once

class Board{
    Graph _graph;
    Land _lands[19];

    void init();

public:
    Board(){init();}

    bool placeProperty(Property& property,bool firstTurn,int x,int y);

    vector<ResourceCard> getResources(int id,int rand,bool firstTurn);

    vector<ResourceCard> getInitialResources(int id);

};
