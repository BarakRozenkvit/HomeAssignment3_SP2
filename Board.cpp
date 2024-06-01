#include "Board.hpp"

void Board::init() {
    // TODO: do it with Random
    Hexagon hexagons[19] = {Hexagon(0, 3, 4, 7, 8, 12),Hexagon(1, 4, 5, 8, 9, 13),
                            Hexagon(2, 5, 6, 9, 10, 14),Hexagon(7, 11, 12, 16, 17, 22),
                            Hexagon(8, 12, 13, 17, 18, 23),Hexagon(9, 13, 14, 18, 19, 24),
                            Hexagon(10, 14, 15, 19, 20, 25),Hexagon(16, 21, 22, 27, 28, 33),
                            Hexagon(17, 22, 23, 28, 29, 34),Hexagon(18, 29, 24, 29, 30, 35),
                            Hexagon(19, 24, 25, 30, 31, 36),Hexagon(20, 25, 26, 31, 32, 37),
                            Hexagon(28, 33, 34, 38, 39, 43),Hexagon(29, 34, 35, 39, 40, 44),
                            Hexagon(30, 35, 36, 40, 41, 45),Hexagon(31, 36, 37, 41, 42, 46),
                            Hexagon(39, 43, 44, 47, 48, 51),Hexagon(40, 44, 45, 48, 49, 52),
                            Hexagon(41, 45, 46, 49, 50, 53)};
    int landNumbers[18] = {2,3,3,4,4,5,
                            5,6,6,8, 8,9,
                            9,10,10,11,11,12};

    _lands[0] = Land("Dessert","", hexagons[10], -1);
    _lands[1] = Land("Agricultural","Wheat", hexagons[11], landNumbers[12]);
    _lands[2] = Land("Agricultural","Wheat", hexagons[12], landNumbers[8]);
    _lands[3] = Land("Agricultural","Wheat", hexagons[8], landNumbers[7]);
    _lands[4] = Land("Agricultural","Wheat", hexagons[7], landNumbers[4]);
    _lands[5] = Land("Pasture","Wool", hexagons[4], landNumbers[11]);
    _lands[6] = Land("Pasture", "Wool",hexagons[0], landNumbers[5]);
    _lands[7] = Land("Pasture", "Wool",hexagons[5], landNumbers[3]);
    _lands[8] = Land("Pasture", "Wool",hexagons[3], landNumbers[9]);
    _lands[9] = Land("Forest","Wood", hexagons[9], landNumbers[16]);
    _lands[10] = Land("Forest","Wood",  hexagons[16], landNumbers[17]);
    _lands[11] = Land("Forest", "Wood", hexagons[17], landNumbers[15]);
    _lands[12] = Land("Forest", "Wood", hexagons[15], landNumbers[2]);
    _lands[13] = Land("Mountain", "Iron", hexagons[2], landNumbers[6]);
    _lands[14] = Land("Mountain","Iron", hexagons[6], landNumbers[0]);
    _lands[15] = Land("Mountain","Iron", hexagons[18], landNumbers[14]);
    _lands[16] = Land("Hills","Brick", hexagons[14], landNumbers[1]);
    _lands[17] = Land("Hills","Brick", hexagons[1], landNumbers[13]);
    _lands[18] = Land("Hills", "Brick",hexagons[13], landNumbers[10]);
}

bool Board::canPlaceProperty(string property,char id,bool isFirstTurn,int i,int j) {
    if (property == "Road") {
        if (_graph.getValue(i,i) == id + 1 || _graph.getValue(i,i) == id + 2 ||
            _graph.getValue(j,j) == id + 1 || _graph.getValue(j,j) == id + 2) {
            return true;
        }
        for (int k = 0; k < _graph.size(); k++) {
            if (_graph.getValue(i,k) == id || _graph.getValue(j,k) == id) {
                return true;
            }
        }
    } else if (property == "Village") {
        bool noAdj = false, isPath = false;
        // scan for neighbors
        for (int k = 0; k < _graph.size(); k++) {
            if (_graph.getValue(i,k) == id) { isPath = true; }
            // what is neighbors and check if no village there
            if (_graph.getValue(i,k) >= 1 && _graph.getValue(k,k) == 0) { noAdj = true; }
        }

        if(noAdj && isFirstTurn) {return true;}
        if (noAdj && isPath) { return true; }
        return false;

    }
    else if(property == "City") {
        if (_graph.getValue(i,j) == id + 2 - 1) {
            return true;
        }
    }
    return false;
}

void Board::placeProperty(string property, char id, int x, int y) {
    if (property == "Road") {
        _graph.setValue(id+0,x,y);
    }
    else if (property == "Village") {
        _graph.setValue(id+1,x,y);
    }
    else if(property == "City") {
        _graph.setValue(id+2,x,y);
    }
}

Set<ResourceCard> Board::getResources(char id,bool isFirstTurn,int rand){
    Set<ResourceCard> resources;
    for(int i=0;i<_graph.size();i++){
        int amount = _graph.getValue(i,i) - id;
        if (amount < 0 || amount > 2){ continue;}
        for(int j=0;j<19;j++){
            if(_lands[j].sitOn(i) && (_lands[j].getValue() == rand|| isFirstTurn)){
                if(_lands[j].getResourceType() == ""){ continue;}
                resources.add(_lands[j].getResourceType(),amount);
            }
        }
    }
    return resources;
}

//void Board::moveGambit(){}


