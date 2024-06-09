//314638669 | Barak10101998@gmail.com
#include "Property.hpp"

Property::Property(string type,int amount): Countable(amount), Identifiable(type){
    _cost = GameSet<ResourceCard>();
    if(type == "Road"){
        _pointsVal = 0;
        _cost.add("Brick",1);
        _cost.add("Wood",1);
    }
    else if(type == "Village"){
        _pointsVal = 1;
        _cost.add("Brick",1);
        _cost.add("Wood",1);
        _cost.add("Wool",1);
        _cost.add("Wheat",1);
    }
    else if(type == "City"){
        _pointsVal = 2;
        _cost.add("Iron",3);
        _cost.add("Wheat",2);
    }
    else{
        throw invalid_argument("Invalid property created");
    }
}