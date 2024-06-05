#include "Land.hpp"
#include "Graph.hpp"
#include "Property.hpp"
#include "DevelopmentCard.hpp"
#pragma once

using namespace std;

class Board{
    Graph _graph;
    Land _lands[19];
    Set<DevelopmentCard> _developmentCards;

    void init();

public:
    Board(){init();}

    bool canBuild(string property, char id, int turnCounter, int x, int y);

    void build(string property, char id, int x, int y);

    Set<ResourceCard> getResources(char id,int turnCounter,int rand);

    DevelopmentCard& getDevelopmentCard(string type){
        if(_developmentCards.size() == 0) {
            throw invalid_argument("No development Cards");
        }
        int res = _developmentCards.search(type);
        if(res == -1){
            throw invalid_argument("no Development card with this name");
        }
        _developmentCards.getAt(res).remove(1);
        return _developmentCards.getAt(res);
    }

    friend ostream& operator<<(ostream& out,Board& b){
        out << b._graph <<endl;
        return out;
    }

};
