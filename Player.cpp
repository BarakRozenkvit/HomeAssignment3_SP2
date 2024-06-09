#include "Player.hpp"

Player::Player(string name,int id): _name(name), _winPoints(0),_id(id){
    _properties.add("Road",15);
    _properties.add("Village",5);
    _properties.add("City",4);
    _isTurn = false;
};

bool Player::canPay(GameSet<Card>& toPay) {
    if(!_turnCounter){return true;}
    return _cards.contains(toPay);
}

void Player::pay(GameSet<Card> &toPay) {
    if (_turnCounter > 0) {
        if (!canPay(toPay)) {
            throw invalid_argument("Not Enough Funds to Pay");
        }
        _cards -= toPay;
    }
}

void Player::build(string type, Board& board, int x, int y) {
    // if not your turn and not your first turn
    if(!_isTurn && _turnCounter){
        throw invalid_argument("Not" + _name + "Turn");
    }
    // if property not exist
    if(_properties.search(type) == -1){
        throw invalid_argument("No Property Exist");
    }
    // if invalid place to build
    if(!board.canBuild(type, _id, _turnCounter, x, y)){
        throw invalid_argument("Invalid Place to build");
    }

    Property property = Property(type,1);
    GameSet<Card> set = GameSet<Card>(property.getCost());
    pay(set);

    board.build(type, _id, x, y);
    _properties.remove(type,1);
    _winPoints += property.getWinPoints();
    if(type == "City"){
        _properties.add("Village",1);
        _winPoints -= Property("Village",1).getWinPoints();
    }
}

void Player::useDevelopmentCard(string type){
    DevelopmentCard card = DevelopmentCard(type,1);
    if(!_isTurn){
        throw invalid_argument("Not his turn!");
    }
    int res = _cards.search(card.getType());
    if(res == -1){
        throw invalid_argument("Development Card not found");
    }
    Card& devCard = _cards.getAt(res);
    DevelopmentCard& result = static_cast<DevelopmentCard&>(devCard);
    result.flashCard();
    if(card.getType() == "Monopoly" || card.getType() == "Builder" || card.getType() == "WealthyYear"){
        _cards.remove(card.getType(),card.size());
    }
}

void Player::buyDevelopmentCard(string type, Board &board){
    DevelopmentCard temp = DevelopmentCard(type, 1);
    if (!_isTurn) {
        throw invalid_argument("Not your Turn");
    }
    GameSet<Card> resource = GameSet<Card>(temp.getCost());
    if (!canPay(resource)) {
        throw invalid_argument("Not Funds ");
    }
    DevelopmentCard card = board.getDevelopmentCard(temp.getType());
    if (type == "WinningPoints") {
        _winPoints++;
    }
    _cards.add(card.getType(), 1);
    pay(resource);
}

void Player::useWealthyYearCard(string resource1, string resource2){
    useDevelopmentCard("WhealthyYear");
    _cards.add(resource1, 1);
    _cards.add(resource2, 1);
    endTurn();
}

void Player::useBuilderCard(int x1, int y1, int x2, int y2, Board& board){
    bool placeValid1 = board.canBuild("Road", getID(), _turnCounter, x1, y1);
    bool placeValid2 = board.canBuild("Road", getID(), _turnCounter, x2, y2);
    if (placeValid1 && placeValid2) {
        useDevelopmentCard("Builder");
        int temp = _turnCounter;
        _turnCounter = 0;
        build("Road", board, x1, y1);
        build("Road", board, x2, y2);
        _turnCounter = temp;
    }
    endTurn();
}

void Player::useMonopolyCard(string desiredResource, Player *p, Player *m){
    if (m == p || m == this || p == this) {
        throw invalid_argument("must include all participants");
    }
    useDevelopmentCard("Monopoly");
    GameSet<Card> wallet;
    GameSet<ResourceCard> desired;desired.add(desiredResource, 1);
    GameSet<Card> dest = GameSet<Card>(desired);
    if (p->canPay(dest)) {
        p->pay(dest);
        wallet += dest;
    }
    if (m->canPay(dest)) {
        m->pay(dest);
        wallet += dest;
    }
    receive(wallet);
    endTurn();
}

int Player::useKnightCard(){
    useDevelopmentCard("Knight");
    int i = _cards.search("Knight");
    Card& devCard = _cards.getAt(i);
    DevelopmentCard& result = static_cast<DevelopmentCard&>(devCard);
    endTurn();
    return result.getAmountFlashed();
}

bool Player::receive(GameSet<Card>& resources){
    _cards += resources;
    return true;
}

void Player::removeHalf(GameSet<ResourceCard>& set) {
    int size = 0;
    for(int i=0;i<_cards.size();i++){
        Card& card = _cards.getAt(i);
        try{
            ResourceCard res = ResourceCard(card.getType(),1);
            size += card.size();
        }
        catch (const exception& exc) {
            continue;
        }
    }
    if (size < 7) {
        throw invalid_argument("Cant reduce resources");
    }
    GameSet<Card> set2 = GameSet<Card>(set);
    pay(set2);
}

void Player::trade(GameSet<Card> mySet, Player *player, GameSet<Card> playerSet) {
    if (player == this) {
        throw invalid_argument("Cant trade with yourself");
    }
    if (!_isTurn) {
        throw invalid_argument("Not my turn");
    }
    if (canPay(mySet) && player->canPay(playerSet)) {
        pay(mySet);
        player->pay(playerSet);
        receive(playerSet);
        player->receive(mySet);
    } else {
        throw invalid_argument("Invalid Trade");
    }
}


