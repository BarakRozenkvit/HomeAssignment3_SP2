#include "Player.hpp"
#include <iostream>

Player::Player(std::string name,int id): _name(name), _winPoints(2),_id(id){
    _resourceCards.add("Resource","Wood",0);
    _resourceCards.add("Resource","Wheat",0);
    _resourceCards.add("Resource","Wool",0);
    _resourceCards.add("Resource","Brick",0);
    _resourceCards.add("Resource","Iron",0);
    _properties.add("Road",13);
    _properties.add("Village",3);
    _properties.add("City",4);
};

bool Player::payToBuild(std::string property, bool firstTurn) {
    Property* result = _properties.search(property);
    if(!firstTurn){
        _resourceCards -= result->getCost();
    }
    _properties -= *result;
}

bool Player::buyDevelopmentCard(string type,string name){
    _developmentCard.add(type,name,1);
    Card* card = _developmentCard.search(name);
    CardSet cardset = static_cast <DevelopmentCard*>(card)->getCost();
    _resourceCards -= cardset;
}

bool Player::flashDevelopmentCard(string name){
    Card* card = _developmentCard.search(name);
    static_cast <DevelopmentCard*>(card)->flashCard();
}

bool Player::getResources(CardSet& cardset) {
    _resourceCards += cardset;
}

bool Player::giveResources(CardSet& cardset) {
    _resourceCards -= cardset;
}

//void Player::print(){
//    cout<<endl;
//    cout << "Name: " << _name << endl;
//    cout << "Winning Points: " << _winPoints<<endl;
//    cout<<"Resource Cards: ";
//    for (int i = 0; i < _resourceCards.size(); i++) {
//        cout << "[" << _resourceCards[i].getResource() << " : " << _resourceCards[i].getAmount()<<"], ";
//
//    }
//    cout<<endl;
//    cout<<"Development Cards: ";
//    for (int i = 0; i < _developmentCard.size(); i++) {
//        if(_developmentCard[i]->getFeature() == "Promotion"){
//            PromotionCard* castPromotion = static_cast<PromotionCard*>(_developmentCard[i]);
//            cout << "[" << castPromotion->getBenefit() << " : " << castPromotion->getAmount()<<"], ";
//        }
//        else {
//            cout << "[" << _developmentCard[i]->getFeature() << " : " << _developmentCard[i]->getAmount() << "], ";
//        }
//    }
//    cout<<endl;
//}
//
//void Player::addDevelopmentCard(string type) {
//    for(int i=0;i<_developmentCard.size();i++){
//        if(_developmentCard[i]->getFeature() == type){
//            _developmentCard[i]->addAmount(1);
//            return;
//        }
//        if(_developmentCard[i]->getFeature() == "Promotion"){
//            if(static_cast<PromotionCard*>(_developmentCard[i]) ->getBenefit() == type){
//                _developmentCard[i]->addAmount(1);
//                return;
//            }
//        }
//    }
//    _developmentCard.push_back(new DevelopmentCard(type));
//    return;
//}
