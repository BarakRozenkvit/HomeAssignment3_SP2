#include "Card.hpp"
#include <vector>
#include <iostream>

#pragma once
class Property{
    std::string _type;
    std::vector<ResourceCard> _cost;
    int _owner_id;
    int _pointsVal;
    int _amount;

public:
    Property(std::string type,int amount,int owner_id): _type(type),_amount(amount),_owner_id(owner_id){
        if(type == "Road"){
            _pointsVal = 0;
            _cost = {ResourceCard("Brick",1),ResourceCard("Wood",1)};
        }
        else if(type == "Village"){
            _pointsVal = 1;
            _cost = {ResourceCard("Brick",1),ResourceCard("Wood",1),
                     ResourceCard("Wool",1),ResourceCard("Wheat",1)};
        }
        else if(type == "City"){
            _pointsVal = 2;
            _cost = {ResourceCard("Iron",3),ResourceCard("Wheat",2)};
        }
        else{
            std::cout << "Error" << std::endl;
        }
    }

    std::string getType(){return _type;}

    std::vector<ResourceCard>& getCost(){return _cost;}

    int getPointsValue(){return _pointsVal;}

    int getOwnerID(){return _owner_id;}

    void removeAmount(int amount){_amount -= amount;}


};