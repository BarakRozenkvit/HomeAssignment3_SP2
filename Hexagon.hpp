class Hexagon{
    int _vertices[6] = {};

public:
    Hexagon(){}
    Hexagon(int v0,int v1, int v2, int v3, int v4, int v5){
        _vertices[0] = v0;_vertices[1] = v1;
        _vertices[2] = v2;_vertices[3] = v3;
        _vertices[4] = v4;_vertices[5] = v5;
    }
};