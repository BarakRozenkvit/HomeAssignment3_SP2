#include "Hexagon.hpp"
#include "Land.hpp"
#include "Graph.hpp"
#include "Property.hpp"
#include "Player.hpp"
#pragma once

using namespace std;

class Board{
    Graph _graph;
    Land _lands[19];

    void init();

public:
    Board(){init();}

    bool placeProperty(string property,char id,bool isFirstTurn,int x,int y);

    Set<ResourceCard> getResources(char id,bool isFirstTurn,int rand);

    void moveGambit();

    friend ostream& operator<<(ostream& out,Board& b){
        out << b._graph <<endl;
        return out;
    }

};
