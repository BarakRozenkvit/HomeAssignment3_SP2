#pragma once

class Countable{
    int _amount = 0;

public:
    Countable(){};
    Countable(int amount): _amount(amount){};
    virtual void add(int amount){_amount += amount;}
    virtual void remove(int amount){_amount -= amount;}
    virtual int size() {return _amount;}
    virtual void clear(){_amount=0;}
};
