#include "Land.hpp"

bool Hexagon::contains(int n) {
    for(int i=0;i<_vertices.size();i++){
        if(_vertices[i] == n){
            return true;
        }
    }
    return false;
}