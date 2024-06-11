#include "Card.hpp"


ResourceCard::ResourceCard(std::string type, int amount): Card(type,amount) {
    bool resource = type == "Wool" || type == "Wood" || type == "Wheat" || type == "Iron" || type == "Brick";
    if(!resource){
        throw invalid_argument("No card in this game");
   }
}

DevelopmentCard::DevelopmentCard(std::string type, int amount) : Card(type,amount){
    bool development = type == "Knight" || type == "WinningPoints" || type == "Monopoly" || type == "Builder" ||
                       type == "WealthyYear";
    if(!development) {
        throw invalid_argument("No card in this game");
    }
    _cost.add("Iron",1);
    _cost.add("Wool",1);
    _cost.add("Wheat",1);
}