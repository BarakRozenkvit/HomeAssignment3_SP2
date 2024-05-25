#pragma once
#include <string>
#include <vector>

using namespace std;

class Card{
    string _type;
    string _name;
    int _amount;

public:
    Card(string type,int amount): _type(type),_amount(amount){};
    Card(string type): _type(type), _amount(0){};
    Card(string type,string name,int amount): _type(type), _name(name), _amount(amount){};

    string getType(){return _type;}
    string getName(){return _name;}

    void add(int amount){_amount += amount;}
    void remove(int amount){_amount -= amount;}
    int size(){return _amount;}
    void clear(){_amount=0;}
};

class CardSet{
    vector<Card> _cards;

public:
    CardSet();

    Card* search(string name);

    void add(string type,string name,int amount);

    void remove(string name,int amount);

    Card* getAt(int idx);

    int size();

    CardSet& operator-=(CardSet& cardset){
        for(int i=0;i<cardset.size();i++){
            Card* other_card = cardset.getAt(i);
            Card* this_card = search(other_card->getName());
            this_card->remove(other_card->size());
        }
        return *this;
    }

    CardSet& operator+=(CardSet& cardset){
        for(int i=0;i<cardset.size();i++){
            Card* other_card = cardset.getAt(i);
            Card* this_card = search(other_card->getName());
            this_card->add(other_card->size());
        }
        return *this;
    }
};

class ResourceCard : public Card{

public:
    ResourceCard(std::string resource,int amount): Card("c",resource,amount){};
    ResourceCard(std::string resource): Card("Resource",resource,0){};
};

class DevelopmentCard : public Card{
    int _flashedAmount = 0;
    CardSet _cost;

public:
    DevelopmentCard(string name);
    DevelopmentCard(string name,int amount);
    ~DevelopmentCard(){};

    bool amountFlashed(){return _flashedAmount;}
    void flashCard(){_flashedAmount++;}
    CardSet& getCost(){return _cost;}
};