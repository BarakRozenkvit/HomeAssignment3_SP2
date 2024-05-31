#include <vector>
#pragma once
using namespace std;

class Graph {

    vector<vector<char>> _adjMatrix;

    public:
        Graph();
        bool setValue(char val,int i,int j);
        char getValue(int i,int j);
        int size(){return _adjMatrix.size();}
};
