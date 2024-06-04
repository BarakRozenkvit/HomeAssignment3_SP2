#include <string>
#include "ResourceCard.hpp"
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

        string getResourceType(){return _resource;}

        int getValue(){return _value;}
};