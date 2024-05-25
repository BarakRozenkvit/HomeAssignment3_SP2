#pragma once
#include <string>
#include <vector>

class Card{
    std::string _type;
    int _amount;

public:
    Card(std::string type,int amount): _type(type),_amount(amount){};
    Card(std::string type): _type(type), _amount(0){};
    void add(){_amount++;}
    void addAmount(int amount){_amount += amount;}
    void remove(int amount){_amount -= amount;}
    int getAmount(){return _amount;}
    std::string getType(){return _type;}
    void clear(){_amount=0;}
};

class ResourceCard : public Card{
    std::string _resource;

public:
    ResourceCard(std::string resource,int amount): _resource(resource),Card("Resource",amount){};
    ResourceCard(std::string resource): _resource(resource),Card("Resource",0){};

    std::string getResource(){return _resource;}
};

//class ResourceCard{
//    std::string _type;
//    int _amount;
//
//public:
//    ResourceCard(std::string type,int amount): _type(type),_amount(amount){};
//    ResourceCard(std::string type): _type(type), _amount(0){};
//    void add(){_amount++;}
//    void addAmount(int amount){_amount += amount;}
//    void remove(int amount){_amount -= amount;}
//    int getAmount(){return _amount;}
//    std::string getType(){return _type;}
//
//};

class DevelopmentCard : public Card{
    std::string _feature;
    int _flashedAmount = 0;
    std::vector<ResourceCard> _cost = {ResourceCard("Iron",1),
                                       ResourceCard("Wool",1),
                                       ResourceCard("Wheat",1)};


public:
    DevelopmentCard(std::string feature): _feature(feature), Card("Development",0){};
    DevelopmentCard(std::string feature,int amount): _feature(feature), Card("Development",amount){};
    ~DevelopmentCard(){};

    std::string getFeature(){return _feature;}
    bool amountFlashed(){return _flashedAmount;}
    void flashCard(){_flashedAmount++;}
};

class PromotionCard: public DevelopmentCard{
    std::string _benefit;

public:
    PromotionCard(std::string benefit): _benefit(benefit), DevelopmentCard("Promotion",1){};
    ~PromotionCard(){};

    std::string  getBenefit(){return _benefit;}

};



//class Knights: public Development{};
//class WinPoints: public Development{};
//
//class Monopol: public Promotion{
//    Resource desired_resource;
//};
//class Builder: public Promotion{};
//class WealthyYear: public Promotion{};