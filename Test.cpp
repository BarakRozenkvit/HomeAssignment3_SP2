#include "doctest.h"
#include "Catan.hpp"

Player* p1;
Player* p2;
Player* p3;
Catan catan;

void setUP(){
    p1 = new Player("P1", 10);
    p2 = new Player("P2", 20);
    p3 = new Player("P3", 30);
    catan = Catan(p1, p2, p3);
}

TEST_CASE("Set Class"){
    Set<Card> set1;
    Set<Card> set2;
    set1.add("Wood",1);
    CHECK(set1.toString() == "[Wood: 1],");

    set1.add("Wood",2);
    CHECK(set1.toString() == "[Wood: 3],");

    set1.remove("Wood",2);
    CHECK(set1.toString() == "[Wood: 1],");

    set1.remove("Wood",1);
    CHECK(set1.toString() == "");

    set1.add("Wood",1);
    CHECK(set1.contains(set2));

    CHECK_FALSE(set2.contains(set1));
    set2.add("Wood",3);
    CHECK(set2.contains(set1));
    set1.add("Wood",2);
    set1.add("Wool",1);
    CHECK(set1.contains(set2));
    CHECK_FALSE(set2.contains(set1));
    set1.clear();
    set2.clear();
    CHECK(set1.toString() == "");
    set1.add("Wood",1);
    set2.add("Wool",1);
    CHECK_FALSE(set1.contains(set2));
    CHECK_FALSE(set2.contains(set1));
}

TEST_CASE("Check Throws when not enough resources to pay"){
    setUP();
    p1->startTurn();
    Set<Card> receive;receive.add("Wool",1);receive.add("Wood",3);
    p1->receive(receive);
    Set<Card> pay;pay.add("Wool",1);pay.add("Wood",3);pay.add("Iron",1);
    CHECK_THROWS(p1->pay(pay));
}
TEST_CASE("Check Throws when creating card not exist in game"){
    setUP();
    Set<Card> receive;
    CHECK_THROWS(receive.add("Crystal",1));
}

TEST_CASE("Check using Development card when has no Development Cards") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    CHECK_THROWS(p1->useKnightCard());
}
TEST_CASE("Check has no specific Development Card") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    Set<Card> receove = reinterpret_cast<Set<Card>&>(KnightCard.getCost());
    p1->receive(receove);
    p1->buyDevelopmentCard("Knight",catan.getBoard());
    DevelopmentCard monopolyCard = DevelopmentCard("Monopoly",1);
    CHECK_THROWS(p1->useMonopolyCard("Wool",p2,p3));
}
TEST_CASE("Check continues turn after use Development Card") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    p1->receive(reinterpret_cast<Set<Card>&> (KnightCard.getCost()));
    p1->buyDevelopmentCard("Knight",catan.getBoard());
    p1->useKnightCard();
    CHECK_THROWS(p1->build("Road", catan.getBoard(), 48, 44));
}
TEST_CASE("Check use card that bought in the same round"){}
TEST_CASE("Check if bank of Development Card is empty"){}
TEST_CASE("Check if Development Card is not in Bank"){
    setUP();
    p1->startTurn();
    DevelopmentCard card = DevelopmentCard("WealthyYear",1);
    p1->receive(reinterpret_cast<Set<Card>&>(card.getCost()));
    p1->buyDevelopmentCard("WealthyYear",catan.getBoard());
    p1->receive(reinterpret_cast<Set<Card>&>(card.getCost()));
    CHECK_THROWS(p1->buyDevelopmentCard("WealthyYear",catan.getBoard()));
}

TEST_CASE("build property when you are out of properties"){}
TEST_CASE("build property when you are out of specific property"){}

TEST_CASE("ל Check build road in place that is not exist"){
    setUP();
    p1->startTurn();
    CHECK_THROWS(p1->build("Road",catan.getBoard(),48,49));
}
TEST_CASE("build road in place that is taken"){
    setUP();
    p2->build("Village",catan.getBoard(),5,5);
    p2->build("Road",catan.getBoard(),5,2);
    p2->build("Road",catan.getBoard(),6,2);
    p2->endTurn();
    p1->build("Village",catan.getBoard(),6,6);
    CHECK_THROWS(p1->build("Road",catan.getBoard(),6,2));
}
TEST_CASE("build road not next to your village"){
    setUP();
//    p2->startTurn();
    CHECK_THROWS(p2->build("Road",catan.getBoard(),5,2));
    p2->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p2->build("Road",catan.getBoard(),6,10));
}

TEST_CASE("build village in place that is not exist"){
    setUP();
    p1->startTurn();
    CHECK_THROWS(p1->build("Village",catan.getBoard(),5,50));
    CHECK_THROWS(p1->build("Village",catan.getBoard(),100,100));
    CHECK_THROWS(p1->build("Village",catan.getBoard(),-100,-100));
}
TEST_CASE("build village in place already been placed"){
    setUP();
    p1->build("Village",catan.getBoard(),48,48);
    CHECK_THROWS(p1->build("Village",catan.getBoard(),48,48));
    CHECK_THROWS(p2->build("Village",catan.getBoard(),48,48));
}
TEST_CASE("build village in place not next to your road, not in first turn"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    p1->build("Road",catan.getBoard(),5,2);
    p1->build("Road",catan.getBoard(),2,6);
    p1->startTurn();
    Set<Card> set = reinterpret_cast<Set<Card>&>(Property("Village",1).getCost());
    p1->receive(set);
    CHECK_THROWS(p1->build("Village",catan.getBoard(),10,10));
}
TEST_CASE("build village in place near other Village"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p2->build("Village",catan.getBoard(),2,2));
}

TEST_CASE("build city in the first turn") {
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p1->build("City", catan.getBoard(), 5, 5));
}
TEST_CASE("build city not on your village"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    p1->startTurn();
    Set<Card> set = reinterpret_cast<Set<Card>&>(Property("City",1).getCost());
    p1->receive(set);
    CHECK_THROWS(p1->build("City",catan.getBoard(),8,8));
}

TEST_CASE("Check Trade with yourself"){
    setUP();
    p1->startTurn();
    Set<Card> set;
    Set<Card> set2;
    CHECK_THROWS(p1->trade(set,p1,set2));
}

TEST_CASE("Check Dice is 7 remove resources from player with under 7 cards"){
    setUP();
    p1->startTurn();
    Set<Card> set;set.add("Wool",6);
    Set<ResourceCard> remove;remove.add("Wool",2);
    p1->receive(set);
    CHECK_THROWS(p1->removeHalf(remove));
}

TEST_CASE("Check p2 end turn and p2 roll dice"){
    setUP();
    p2->endTurn();
    CHECK_THROWS(p2->rollDice());
}