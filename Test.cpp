//314638669 | Barak10101998@gmail.com
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

// Test Code

TEST_CASE("GameSet Class"){
    GameSet<Card> set1;
    GameSet<Card> set2;
    set1.add("Wood",1);
    CHECK(set1.toString() == "[Wood: 1],");

    set1.add("Wood",2);
    CHECK(set1.toString() == "[Wood: 3],");

    GameSet<ResourceCard> res = (GameSet<ResourceCard>)set1;
    CHECK(res.toString() == "[Wood: 3],");

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

TEST_CASE("Remove Half"){
    setUP();
    p1->startTurn();
    GameSet<Card> res;
    res.add("Wool",4);res.add("Wood",4);
    p1->receive(res);
    p1->endTurn();

    p2->startTurn();
    p2->rollDice(7);
    GameSet<ResourceCard> toCut;
    toCut.add("Wool",4);
    p1->removeHalf(toCut);
    CHECK(p1->toString() == "P1: [Wood: 4],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
}

TEST_CASE("build"){
    setUP();
    p1->build("Village",catan.getBoard(),48,48);
    p1->build("Road",catan.getBoard(),48,44);
    p1->build("Road",catan.getBoard(),39,44);
    CHECK(p1->toString() == "P1: [Road: 13],[Village: 4],[City: 4],\nWinPoints: 1");
    p1->startTurn();
    GameSet<Card> set;
    set.add("Brick",1);
    set.add("Wood",1);
    set.add("Wool",1);
    set.add("Wheat",1);
    p1->receive(set);
    p1->build("Village",catan.getBoard(),39,39);
    CHECK(p1->toString() == "P1: [Road: 13],[Village: 3],[City: 4],\nWinPoints: 2" );
}

TEST_CASE("trade"){
    setUP();
    p2->startTurn();
    p2->endTurn();
    GameSet<Card> t;t.add("Monopoly",1);t.add("Iron",2);
    GameSet<Card> s;s.add("Wood",3);
    p1->receive(t);
    p2->receive(s);
    p1->startTurn();
    CHECK(p1->toString() == "P1: [Monopoly: 1],[Iron: 2],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p2->toString() == "P2: [Wood: 3],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    p1->trade(t,p2,s);
    CHECK(p1->toString() == "P1: [Wood: 3],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p2->toString() == "P2: [Monopoly: 1],[Iron: 2],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
}

TEST_CASE("buy Development Card"){
    setUP();
    p1->startTurn();
    GameSet<Card> r;
    r.add("Iron",1);
    r.add("Wool",1);
    r.add("Wheat",1);
    p1->receive(r);
    p1->buyDevelopmentCard("Knight", catan.getBoard());
    CHECK(p1->toString() == "P1: [Knight: 1],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
}

TEST_CASE("use WealthyYear Card"){
    setUP();
    p1->startTurn();
    GameSet<Card> r;r.add("WealthyYear",1);
    p1->receive(r);
    p1->useWealthyYearCard("Wool","Wool");
    CHECK(p1->toString() == "P1: [Wool: 2],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
}

TEST_CASE("use Knight Card and Largest army"){
    int size =0 ;
    p1->startTurn();
    GameSet<Card> res;res.add("Knight",3);
    p1->receive(res);
    size= p1->useKnightCard();
    catan.checkLargestArmy(p1,size);
    p1->startTurn();
    size = p1->useKnightCard();
    catan.checkLargestArmy(p1,size);
    p1->startTurn();
    size =p1->useKnightCard();
    catan.checkLargestArmy(p1,size);
    CHECK(catan.getLargestArmy() == p1);
    res.add("Knight",1);
    p2->startTurn();
    p2->receive(res);
    size= p2->useKnightCard();
    catan.checkLargestArmy(p2,size);
    p2->startTurn();
    size = p2->useKnightCard();
    catan.checkLargestArmy(p2,size);
    p2->startTurn();
    size =p2->useKnightCard();
    catan.checkLargestArmy(p2,size);
    p2->startTurn();
    size =p2->useKnightCard();
    catan.checkLargestArmy(p2,size);
    CHECK(catan.getLargestArmy() == p2);
}

TEST_CASE("use Builder card"){
    setUP();
    p1->build("Village",catan.getBoard(),48,48);
    p1->startTurn();
    GameSet<Card> r;r.add("Wood",1);r.add("Builder",1);
    p1->receive(r);
    p1->useBuilderCard(48,44,44,39,catan.getBoard());
    CHECK(p1->toString() == "P1: [Wood: 1],[Road: 13],[Village: 4],[City: 4],\nWinPoints: 1");
}

TEST_CASE("use Monopoly Card"){
    setUP();
    GameSet<Card> s;s.add("Wheat",2);
    GameSet<Card> r;r.add("Wheat",1);r.add("Monopoly",1);
    p1->startTurn();
    p1->receive(r);
    p1->endTurn();
    p2->startTurn();
    p2->receive(s);
    p2->endTurn();
    p3->startTurn();
    p3->receive(s);
    p3->endTurn();
    p1->startTurn();
    CHECK(p1->toString() == "P1: [Wheat: 1],[Monopoly: 1],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p2->toString() == "P2: [Wheat: 2],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p3->toString() == "P3: [Wheat: 2],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    p1->useMonopolyCard("Wheat",p2,p3);
    CHECK(p1->toString() == "P1: [Wheat: 3],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p2->toString() == "P2: [Wheat: 1],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");
    CHECK(p3->toString() == "P3: [Wheat: 1],[Road: 15],[Village: 5],[City: 4],\nWinPoints: 0");

}

TEST_CASE("distribute resources"){
    setUP();
    p1->build("Village", catan.getBoard(), 23, 23);
    p1->build("Road", catan.getBoard(), 23, 29);
    p1->build("Village", catan.getBoard(), 14, 14);
    p1->build("Road", catan.getBoard(), 14, 9);

    p2->build("Village", catan.getBoard(), 45, 45);
    p2->build("Road", catan.getBoard(), 45, 41);
    p2->build("Village", catan.getBoard(), 22, 22);
    p2->build("Road", catan.getBoard(), 41, 36);

    p3->build("Village", catan.getBoard(), 39, 39);
    p3->build("Road", catan.getBoard(), 39, 43);
    p3->build("Village", catan.getBoard(), 47, 47);
    p3->build("Road", catan.getBoard(), 47, 43);

    catan.distributeResources();
    CHECK(p1->toString() == "P1: [Wool: 2],[Iron: 2],[Wheat: 1],[Wood: 1],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
    CHECK(p2->toString() == "P2: [Wheat: 2],[Wool: 1],[Wood: 1],[Iron: 1],[Brick: 1],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
    CHECK(p3->toString() == "P3: [Wheat: 1],[Wood: 2],[Brick: 1],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
    p1->startTurn();
    int rand = p1->rollDice(8);
    catan.distributeResources(rand);
    CHECK(p1->toString() == "P1: [Wool: 2],[Iron: 2],[Wheat: 1],[Wood: 1],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
    CHECK(p2->toString() == "P2: [Wheat: 2],[Wool: 2],[Wood: 1],[Iron: 1],[Brick: 1],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
    CHECK(p3->toString() == "P3: [Wheat: 1],[Wood: 2],[Brick: 2],[Road: 13],[Village: 3],[City: 4],\nWinPoints: 2");
}

TEST_CASE("check winner"){
    setUP();
    p1->addWinningPoints(10);
    CHECK(catan.printWinner() == "P1");
}


// Test Erros

TEST_CASE("Check Throws when not enough resources to pay"){
    setUP();
    p1->startTurn();
    GameSet<Card> receive;receive.add("Wool", 1);receive.add("Wood", 3);
    p1->receive(receive);
    GameSet<Card> pay;pay.add("Wool", 1);pay.add("Wood", 3);pay.add("Iron", 1);
    CHECK_THROWS(p1->pay(pay));
}
TEST_CASE("Check Throws when creating card not exist in game"){
    setUP();
    GameSet<ResourceCard> receive;
    CHECK_THROWS(receive.add("Crystal",1));
}

TEST_CASE("Check Throws using Development card when has no Development Cards") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    CHECK_THROWS(p1->useKnightCard());
}
TEST_CASE("Check Throws has no specific Development Card") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    GameSet<Card> receove = reinterpret_cast<GameSet<Card>&>(KnightCard.getCost());
    p1->receive(receove);
    p1->buyDevelopmentCard("Knight",catan.getBoard());
    DevelopmentCard monopolyCard = DevelopmentCard("Monopoly",1);
    CHECK_THROWS(p1->useMonopolyCard("Wool",p2,p3));
}
TEST_CASE("Check Throws continues turn after use Development Card") {
    setUP();
    p1->startTurn();
    DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
    p1->receive(reinterpret_cast<GameSet<Card>&> (KnightCard.getCost()));
    p1->buyDevelopmentCard("Knight",catan.getBoard());
    p1->useKnightCard();
    CHECK_THROWS(p1->build("Road", catan.getBoard(), 48, 44));
}
TEST_CASE("Check Throws if Development Card is not in Bank"){
    setUP();
    p1->startTurn();
    DevelopmentCard card = DevelopmentCard("WealthyYear",1);
    p1->receive(reinterpret_cast<GameSet<Card>&>(card.getCost()));
    p1->buyDevelopmentCard("WealthyYear",catan.getBoard());
    p1->receive(reinterpret_cast<GameSet<Card>&>(card.getCost()));
    CHECK_THROWS(p1->buyDevelopmentCard("WealthyYear",catan.getBoard()));
}

TEST_CASE("Check Throws build property when you are out of specific property"){
    setUP();
    p1->build("Village",catan.getBoard(),0,0);
    p1->build("Village",catan.getBoard(),1,1);
    p1->build("Village",catan.getBoard(),2,2);
    p1->build("Village",catan.getBoard(),53,53);
    p1->build("Village",catan.getBoard(),52,52);
    CHECK_THROWS(p1->build("Village",catan.getBoard(),51,51));

}

TEST_CASE("ל Check Throws build road in place that is not exist"){
    setUP();
    p1->startTurn();
    CHECK_THROWS(p1->build("Road",catan.getBoard(),48,49));
}
TEST_CASE("Check Throws build road in place that is taken"){
    setUP();
    p2->build("Village",catan.getBoard(),5,5);
    p2->build("Road",catan.getBoard(),5,2);
    p2->build("Road",catan.getBoard(),6,2);
    p2->endTurn();
    p1->build("Village",catan.getBoard(),6,6);
    CHECK_THROWS(p1->build("Road",catan.getBoard(),6,2));
}
TEST_CASE("Check Throws build road not next to your village"){
    setUP();
//    p2->startTurn();
    CHECK_THROWS(p2->build("Road",catan.getBoard(),5,2));
    p2->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p2->build("Road",catan.getBoard(),6,10));
}

TEST_CASE("Check Throws build village in place that is not exist"){
    setUP();
    p1->startTurn();
    CHECK_THROWS(p1->build("Village",catan.getBoard(),5,50));
    CHECK_THROWS(p1->build("Village",catan.getBoard(),100,100));
    CHECK_THROWS(p1->build("Village",catan.getBoard(),-100,-100));
}
TEST_CASE("Check Throws build village in place already been placed"){
    setUP();
    p1->build("Village",catan.getBoard(),48,48);
    CHECK_THROWS(p1->build("Village",catan.getBoard(),48,48));
    CHECK_THROWS(p2->build("Village",catan.getBoard(),48,48));
}
TEST_CASE("Check Throws build village in place not next to your road, not in first turn"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    p1->build("Road",catan.getBoard(),5,2);
    p1->build("Road",catan.getBoard(),2,6);
    p1->startTurn();
    GameSet<Card> set = reinterpret_cast<GameSet<Card>&>(Property("Village", 1).getCost());
    p1->receive(set);
    CHECK_THROWS(p1->build("Village",catan.getBoard(),10,10));
}
TEST_CASE("Check Throws build village in place near other Village"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p2->build("Village",catan.getBoard(),2,2));
}

TEST_CASE("Check Throws build city in the first turn") {
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    CHECK_THROWS(p1->build("City", catan.getBoard(), 5, 5));
}
TEST_CASE("Check Throws build city not on your village"){
    setUP();
    p1->build("Village",catan.getBoard(),5,5);
    p1->startTurn();
    GameSet<Card> set = reinterpret_cast<GameSet<Card>&>(Property("City", 1).getCost());
    p1->receive(set);
    CHECK_THROWS(p1->build("City",catan.getBoard(),8,8));
}

TEST_CASE("Check Throws Check Trade with yourself"){
    setUP();
    p1->startTurn();
    GameSet<Card> set;
    GameSet<Card> set2;
    CHECK_THROWS(p1->trade(set,p1,set2));
}

TEST_CASE("Check Dice is 7 remove resources from player with under 7 cards"){
    setUP();
    p1->startTurn();
    GameSet<Card> set;set.add("Wool", 6);
    GameSet<ResourceCard> remove;remove.add("Wool", 2);
    p1->receive(set);
    CHECK_THROWS(p1->removeHalf(remove));
}

TEST_CASE("Check p2 end turn and p2 roll dice"){
    setUP();
    p2->endTurn();
    CHECK_THROWS(p2->rollDice());
}