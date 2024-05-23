#include "Hexagon.hpp"
#include "Card.hpp"

class Land{
    int _value;
    Hexagon _hexagon;
    Resource _resource;

    public:
        Land(Resource& resource1){
            _resource = resource1;
            _hexagon = Hexagon(); //initialize empty constructor
        }
        void setValue(int value){
            _value = value;
        }
        void setHexagon(const Hexagon& hex){
            _hexagon = hex;
        }
};

class Desert: public Land{

    public:
        Desert(): Land()
};

class Forest: public Land{ public: Forest(Wood woodCard): Land(woodCard){}};

class Hill: public Land{ public: Hill(Brick brickCard): Land(brickCard){}};

class Pasture: public Land{ public:Pasture(Wool woolCard): Land(woolCard){}};

class Agricultural: public Land{ public:Agricultural(Wheat wheatCard): Land(wheatCard){}};

class Mountain: public Land{ public: Mountain(Iron ironCard): Land(ironCard){}};