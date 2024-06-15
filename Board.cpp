#include "Board.hpp"

void Board::init() {
    Hexagon hexagons[19] = {Hexagon(0, 3, 4, 7, 8, 12),Hexagon(1, 4, 5, 8, 9, 13),
                            Hexagon(2, 5, 6, 9, 10, 14),Hexagon(7, 11, 12, 16, 17, 22),
                            Hexagon(8, 12, 13, 17, 18, 23),Hexagon(9, 13, 14, 18, 19, 24),
                            Hexagon(10, 14, 15, 19, 20, 25),Hexagon(16, 21, 22, 27, 28, 33),
                            Hexagon(17, 22, 23, 28, 29, 34),Hexagon(18, 23, 24, 29, 30, 35),
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

    _developmentCards.add("Knight",14);
    _developmentCards.add("WinningPoints",5);
    _developmentCards.add("Monopoly",2);
    _developmentCards.add("Builder",2);
    _developmentCards.add("WealthyYear",1);

}

bool Board::canBuild(string property, char id, int turnCounter, int x, int y) {
    // if x or y are valid
    if(x >= _graph.size() || y>= _graph.size() || x < 0 || y<0){return false;}
    if (property == "Road") {
        // if is taken
        if(_graph.getValue(x, y) != 1 ){return false;}
        // if next to city or village
        if (_graph.getValue(x, x) == id + 1 || _graph.getValue(x, x) == id + 2 ||
            _graph.getValue(y, y) == id + 1 || _graph.getValue(y, y) == id + 2) {
            return true;
        }
        for (int k = 0; k < _graph.size(); k++) {
            // if next to other road
            if (_graph.getValue(x, k) == id || _graph.getValue(y, k) == id) {
                return true;
            }
        }
    } else if (property == "Village") {
        // if x and y doesnt represent vertex
        if(x!=y){return false;}
        // if is taker
        if(_graph.getValue(x, y) != 0){return false;}
        bool noAdj = true, isPath = false;
        // scan for neighbors
        for (int k = 0; k < _graph.size(); k++) {
            if (_graph.getValue(x, k) == id) { isPath = true; }
            // what is neighbors and check if no village there
            if (_graph.getValue(x, k) >= 1 && _graph.getValue(k, k) > 0) {
                return false;
                noAdj = true;
            }
        }
        //if no other villages next and his first turn
        if(noAdj && !turnCounter) {return true;}
        //if no other villages next and next to road
        if (noAdj && isPath) { return true; }
        return false;

    }
    else if(property == "City") {
        // if first turn -> not allowed
        if(!turnCounter){return false;}
        // if no settelment -> not allowed
        if(_graph.getValue(x, y) == 0){return false;}
        if (_graph.getValue(x, y) == id + 2 - 1) {
            return true;
        }
    }
    return false;
}

void Board::build(string property, char id, int x, int y) {
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

GameSet<ResourceCard> Board::getResources(char id, int turnCounter, int rand){
    GameSet<ResourceCard> resources;
    for(int i=0;i<_graph.size();i++){
        // go through all vertices
        int amount = _graph.getValue(i,i) - id;
        // if not belong to id continue
        if (amount < 0 || amount > 2){ continue;}
        // go through all lands
        for(int j=0;j<19;j++){
            // if vertex is on land and random value or first turn
            if(_lands[j].sitOn(i) && (_lands[j].getValue() == rand|| !turnCounter)){
                if(_lands[j].getResourceType() == ""){ continue;}
                resources.add(_lands[j].getResourceType(),amount);
            }
        }
    }
    return resources;
}

DevelopmentCard Board::getDevelopmentCard(std::string type) {
    if(_developmentCards.size() == 0) {
        throw invalid_argument("No development Cards");
    }
    int res = _developmentCards.search(type);
    if(res == -1){
        throw invalid_argument("no Development card with this name");
    }
    DevelopmentCard card = _developmentCards.getAt(res);
    _developmentCards.remove(card.getType(),1);
    return card;
}

