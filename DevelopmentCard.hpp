#include "Identifiable.hpp"
#include "Countable.hpp"
#include "Set.hpp"
#include "ResourceCard.hpp"

class DevelopmentCard: public Identifiable,public Countable{
    Set<ResourceCard> _cost;
    int _flashedAmount;

public:
    DevelopmentCard(string type,int amount): Countable(amount),Identifiable(type){
        _cost.add("Iron",1);
        _cost.add("Wool",1);
        _cost.add("Wheat",1);
    };
    Set<ResourceCard>& getCost(){return _cost;}
    void flashCard(){_flashedAmount++;}
    int getAmountFlashed(){return _flashedAmount;}



};
