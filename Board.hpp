#include "Hexagon.hpp"
#include "Land.hpp"
#include "Graph.hpp"

class Board{
    Graph _graph = Graph();
    Hexagon hexas[19];
    int _landNumbers[18] = {2,3,3,4,4,5,
                           5,6,6,8, 8,9,
                           9,10,10,11,11,12};
    Wool _woolDec = Wool();
    Wood _woodDec = Wood();
    Wheat _wheatDec = Wheat();
    Iron _ironDec = Iron();
    Brick _brickDec = Brick();
    Land lands[19] = {&Desert(), Agricultural(_wheatDec),Agricultural(_wheatDec),Agricultural(_wheatDec),
                      Agricultural(_wheatDec),Pasture(_woolDec),Pasture(_woolDec),Pasture(_woolDec),
                      Pasture(_woolDec),Forest(_woodDec),Forest(_woodDec),Forest(_woodDec),
                      Forest(_woodDec),Mountain(_ironDec),Mountain(_ironDec),Mountain(_ironDec),
                        Hill(_brickDec),Hill(_brickDec),Hill(_brickDec)};

    void init() {
        //Create Hex
        hexas[0] = Hexagon(0, 3, 4, 7, 8, 12);
        hexas[1] = Hexagon(1, 4, 5, 8, 9, 13);
        hexas[2] = Hexagon(2, 5, 6, 9, 10, 14);
        hexas[3] = Hexagon(7, 11, 12, 16, 17, 22);
        hexas[4] = Hexagon(8, 12, 13, 17, 18, 23);
        hexas[5] = Hexagon(9, 13, 14, 18, 19, 24);
        hexas[6] = Hexagon(10, 14, 15, 19, 20, 25);
        hexas[7] = Hexagon(16, 21, 22, 27, 28, 33);
        hexas[8] = Hexagon(17, 22, 23, 28, 29, 34);
        hexas[9] = Hexagon(18, 29, 24, 29, 30, 35);
        hexas[10] = Hexagon(19, 24, 25, 30, 31, 36);
        hexas[11] = Hexagon(20, 25, 26, 31, 32, 37);
        hexas[12] = Hexagon(28, 33, 34, 38, 39, 43);
        hexas[13] = Hexagon(29, 34, 35, 39, 40, 44);
        hexas[14] = Hexagon(30, 35, 36, 40, 41, 45);
        hexas[15] = Hexagon(31, 36, 37, 41, 42, 46);
        hexas[16] = Hexagon(39, 43, 44, 47, 48, 51);
        hexas[17] = Hexagon(40, 44, 45, 48, 49, 52);
        hexas[18] = Hexagon(41, 45, 46, 49, 50, 53);

        //Randomize
        for(int i=0;i<19;i++){
            int c;
            do {
                c=rand()%19;
            }while (hexas[c] == nullptr)
        }

    }

public:
    Board(){init();}

};







};
