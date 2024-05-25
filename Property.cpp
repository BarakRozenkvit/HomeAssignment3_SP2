#include "Property.hpp"

Property::Property(std::string type,int amount): _type(type),_amount(amount),_owner_id(owner_id){
    if(type == "Road"){
        _pointsVal = 0;
        _cost.add("Resource","Brick",1);
        _cost.add("Resource","Wood",1);
    }
    else if(type == "Village"){
        _pointsVal = 1;
        _cost.add("Resource","Brick",1);
        _cost.add("Resource","Wood",1);
        _cost.add("Resource","Wool",1);
        _cost.add("Resource","Wheat",1);
    }
    else if(type == "City"){
        _pointsVal = 2;
        _cost.add("Resource","Iron",3);
        _cost.add("Resource","Wheat",2);
    }
}

PropertySet::PropertySet() {
    _properties = {};
}

Property* PropertySet::search(std::string type) {
    for(int i=0;i<_properties.size();i++){
        if(_properties[i].getType() == type){
            return &_properties[i];
        }
    }
    return nullptr;
}

void PropertySet::add(std::string type, int amount) {
    Property* result = search(type);
    if(result == nullptr){
        _properties.push_back(Property(type,amount));
    }
    result->add(amount);
}

void PropertySet::remove(std::string type, int amount) {
    Property* result = search(type);
    if(result != nullptr){
    result->remove(amount);
    }
}
