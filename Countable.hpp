#pragma once

class Countable{
    int _amount = 0;

public:
    Countable(){};
    Countable(int amount): _amount(amount){};
    void add(int amount){_amount += amount;}
    void remove(int amount){_amount -= amount;}
    int size(){return _amount;}
    void clear(){_amount=0;}
};
