#include <string>
#pragma once

using namespace std;
class Identifiable{
    string _type = "None";
public:
    Identifiable(){}
    Identifiable(string type): _type(type){};
    virtual string getType() const{
        return _type;
    }
};
