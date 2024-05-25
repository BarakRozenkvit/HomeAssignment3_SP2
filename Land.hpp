#include <string>
#include "Card.hpp"
#pragma once

using namespace std;

class Land{
    int _value;
    string _landType;
    Hexagon _hexagon;
    string _resource;

    public:
        Land(){}
        Land(string name,string resource,Hexagon& hexagon,int value) : _landType(name),_resource(resource), _hexagon(hexagon), _value(value){}

        bool sitOn(int n){
            return _hexagon.contains(n);
        }

       ResourceCard getResources(int amount){
           return ResourceCard(_resource,amount);
        }

    string getLandType(){return _landType;}

    string getResourceType(){return _resource;}

    int getValue(){return _value;}
};

//class Desert: public Land{public:Desert(): Land(){}};
//
//class Forest: public Land{ public: Forest(Wood woodCard): Land(woodCard){}};
//
//class Hill: public Land{ public: Hill(Brick brickCard): Land(brickCard){}};
//
//class Pasture: public Land{ public:Pasture(Wool woolCard): Land(woolCard){}};
//
//class Agricultural: public Land{ public:Agricultural(Wheat wheatCard): Land(wheatCard){}};
//
//class Mountain: public Land{ public: Mountain(Iron ironCard): Land(ironCard){}};