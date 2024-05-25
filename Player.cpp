#include "Player.hpp"
#include <iostream>


bool Player::Buy(Property& property) {
    for(int i=0;i<_resourceCards.size();i++){
        for(int j=0;j<property.getCost().size();j++){
            if(_resourceCards[i].getResource() == property.getCost()[i].getResource()){
                if(_resourceCards[i].getAmount() < property.getCost()[i].getAmount()){
                    return false;
                }
            }
        }
    }

    for(int i=0;i<_resourceCards.size();i++){
        for(int j=0;j<property.getCost().size();j++){
            if(_resourceCards[i].getResource() == property.getCost()[i].getResource()){
                _resourceCards[i].remove(property.getCost()[i].getAmount());
            }
        }
    }
    _winPoints += property.getPointsValue();
    return true;
}

bool Player::remove(Property &property) {
    _winPoints -= property.getPointsValue();
    return true;
}

void Player::addResources(vector<ResourceCard>& resources) {
    for(int i=0;i< resources.size();i++){
        for(int j=0;j<_resourceCards.size();j++){
            if(resources[i].getResource() == _resourceCards[j].getResource()){
                _resourceCards[j].addAmount(resources[i].getAmount());
            }
        }

    }
    return;
}

void Player::print(){
    cout<<endl;
    cout << "Name: " << _name << endl;
    cout << "Winning Points: " << _winPoints<<endl;
    cout<<"Resource Cards: ";
    for (int i = 0; i < _resourceCards.size(); i++) {
        cout << "[" << _resourceCards[i].getResource() << " : " << _resourceCards[i].getAmount()<<"], ";

    }
    cout<<endl;
    cout<<"Development Cards: ";
    for (int i = 0; i < _developmentCard.size(); i++) {
        if(_developmentCard[i]->getFeature() == "Promotion"){
            PromotionCard* castPromotion = static_cast<PromotionCard*>(_developmentCard[i]);
            cout << "[" << castPromotion->getBenefit() << " : " << castPromotion->getAmount()<<"], ";
        }
        else {
            cout << "[" << _developmentCard[i]->getFeature() << " : " << _developmentCard[i]->getAmount() << "], ";
        }
    }
    cout<<endl;
}
