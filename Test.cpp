#include "doctest.h"
#include "Catan.hpp"





TEST_CASE("UseKnight"){
    Player* p = new Player("Test",10);
    Player* p1 = new Player("Test",20);
    Player* p2 = new Player("Test",30);
    Catan catan = Catan(p,p1,p2);
    catan.nextPlayer();
    Set<ResourceCard> resources;
    DevelopmentCard card = DevelopmentCard("Knight",1);
    p->addDevelopmentCard(card);
    p->addDevelopmentCard(card);
    p->addDevelopmentCard(card);
    catan.useKnightCard();
    catan.useKnightCard();
    catan.useKnightCard();


}

TEST_CASE("Use Monopoly") {
    Player *p = new Player("Test", 10);
    Player *p1 = new Player("Test", 20);
    Player *p2 = new Player("Test", 30);
    p->setFirstTurn(false);
    p1->setFirstTurn(false);
    p2->setFirstTurn(false);
    Catan catan = Catan(p, p1, p2);
    catan.nextPlayer();
    Set<ResourceCard> resources;
    resources.add("Wheat",1);
    p->receive(resources);
    p1->receive(resources);
    p2->receive(resources);
    DevelopmentCard card = DevelopmentCard("Monopoly", 1);
    p->addDevelopmentCard(card);
    catan.useMonopolyCard("Wheat");
}

TEST_CASE("Use Builder"){
    Player *p = new Player("Test", 10);
    Player *p1 = new Player("Test", 20);
    Player *p2 = new Player("Test", 30);
    Catan catan = Catan(p, p1, p2);
    catan.nextPlayer();
    DevelopmentCard card = DevelopmentCard("Builder", 1);
    p->addDevelopmentCard(card);
    catan.useBuilderCard(32,33,40,39);
}

TEST_CASE("Use WealthyYear"){
    Player *p = new Player("Test", 10);
    Player *p1 = new Player("Test", 20);
    Player *p2 = new Player("Test", 30);
    Catan catan = Catan(p, p1, p2);
    catan.nextPlayer();
    DevelopmentCard card = DevelopmentCard("WealthyYear", 1);
    p->addDevelopmentCard(card);
    catan.useWealthyYearCard("Wheat","Wool");
}