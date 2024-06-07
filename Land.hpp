#include <string>
#include "Card.hpp"
#include <vector>
#pragma once

using namespace std;

class Hexagon{
    vector<int> _vertices;

public:
    Hexagon(){}
    Hexagon(int v0,int v1,int v2,int v3,int v4,int v5){
        _vertices = {v0,v1,v2,v3,v4,v5};
    }
    bool contains(int n){
        for(int i=0;i<_vertices.size();i++){
            if(_vertices[i] == n){
                return true;
            }
        }
        return false;
    }
};

class Land{
    int _value;
    string _landType;
    Hexagon _hexagon;
    string _resource;

    public:
        Land(){}
        Land(string name,string resource,Hexagon& hexagon,int value) : _landType(name),_resource(resource), _hexagon(hexagon), _value(value){}

        bool sitOn(int n){return _hexagon.contains(n);}

        string getResourceType(){return _resource;}

        int getValue(){return _value;}
};