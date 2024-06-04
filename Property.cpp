#include "Property.hpp"

Property::Property(string type,int amount): Countable(amount), Identifiable(type){
    _cost = Set<ResourceCard>();
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
}

//bool Property::operator==(Property property){
//    if(property.getType() == this->getType() && property.size() == this->size()){
//        return true;
//    }
//    return false;
//}
