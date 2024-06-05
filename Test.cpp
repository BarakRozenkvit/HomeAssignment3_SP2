#include "doctest.h"
#include "Catan.hpp"

Player *p1 = new Player("P1", 10);
Player *p2 = new Player("P2", 20);
Player *p3 = new Player("P3", 30);
Catan catan = Catan(p1, p2, p3);


// Player::pay
TEST_CASE("Check Resources pay"){
    SUBCASE("Check Pay"){}
    SUBCASE("Check invalid pay attempt"){
        Set<ResourceCard> receive;receive.add("Wool",1);receive.add("Wood",3);
        p1->receive(receive);
        Set<ResourceCard> pay;pay.add("Wool",1);pay.add("Wood",3);pay.add("Iron",1);
        CHECK_THROWS(p1->pay(pay));
    }
}

// Player::receive
TEST_CASE("Check Resources receive"){
//    SUBCASE("Check receive"){}
    SUBCASE("Check receive resource not exist in game"){
        Set<ResourceCard> receive;receive.add("Crystal",1);
        CHECK_THROWS(p1->receive(receive));
    }
}

// Player::useDevelopmentCard
TEST_CASE("Check Development Card"){
    SUBCASE("Use") {
        SUBCASE("Check use Development Card - Knight") {
            p1->startTurn();
            DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
            CHECK_THROWS(p1->useKnightCard());

        }
        SUBCASE("Check use Development Card - Monopoly") {}
        SUBCASE("Check use Development Card - WhealthyYear") {}
        SUBCASE("Check use Development Card - Builder") {}
        SUBCASE("Check use Development Card - WinPoints") {}
        SUBCASE("Check has no Development Cards") {
            p1->startTurn();
            DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
            CHECK_THROWS(p1->useKnightCard());
        }
        SUBCASE("Check has no specific Development Card") {
            p1->startTurn();
            DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
            Set<ResourceCard> receove = KnightCard.getCost();
            p1->receive(receove);
            p1->buyDevelopmentCard("Knight",catan.getBoard());
            DevelopmentCard monopolyCard = DevelopmentCard("Monopoly",1);
            CHECK_THROWS(p1->useMonopolyCard("Wool",p2,p3));
        }
        SUBCASE("Check continues turn after use Development Card") {
            DevelopmentCard KnightCard = DevelopmentCard("Knight",1);
            p1->useKnightCard();
            CHECK_THROWS(p1->build("Road", catan.getBoard(), 48, 44));
            p1->endTurn();
        }
        SUBCASE("use card that bought in the same round"){}
    }
    SUBCASE("Buy"){
        p1->startTurn();
        SUBCASE("Check if bank of Development Card is empty"){}
        SUBCASE("Check if Development Card is not in Bank"){
            DevelopmentCard card = DevelopmentCard("WealthyYear",1);
            p1->receive(card.getCost());
            p1->buyDevelopmentCard("WealthyYear",catan.getBoard());
            p1->receive(card.getCost());
            p1->buyDevelopmentCard("WealthyYear",catan.getBoard());
        }
    }
}

TEST_CASE("Check Place Property"){
    Player *p1 = new Player("P1", 10);
    Player *p2 = new Player("P2", 20);
    Player *p3 = new Player("P3", 30);
    Catan catan = Catan(p1, p2, p3);
    SUBCASE("Road"){
        SUBCASE("Place in place that is not exist"){
            p1->startTurn();
            CHECK_THROWS(p1->build("Road",catan.getBoard(),48,49));
        }
        SUBCASE("build road in place that is taken"){
            p2->startTurn();
            p2->build("Village",catan.getBoard(),5,5);
            p2->build("Road",catan.getBoard(),5,2);
            p2->build("Road",catan.getBoard(),6,2);
            p2->endTurn();
            p1->startTurn();
            p1->build("Village",catan.getBoard(),6,6);
            CHECK_THROWS(p1->build("Road",catan.getBoard(),6,2));

        }
        SUBCASE("Place not next to your property"){
            p2->startTurn();
            CHECK_THROWS(p2->build("Road",catan.getBoard(),5,2));
            p2->build("Village",catan.getBoard(),5,5);
            CHECK_THROWS(p2->build("Road",catan.getBoard(),6,10));
        }
    }
    SUBCASE("Village"){
        SUBCASE("Place in place that is not exist"){
            p1->startTurn();
            CHECK_THROWS(p1->build("Village",catan.getBoard(),5,50));
            CHECK_THROWS(p1->build("Village",catan.getBoard(),100,100));
            CHECK_THROWS(p1->build("Village",catan.getBoard(),-100,-100));
        }
        SUBCASE("Place in place that already been placed"){
            p1->startTurn();
            p1->build("Village",catan.getBoard(),48,48);
            CHECK_THROWS(p1->build("Village",catan.getBoard(),48,48));
            p1->endTurn();
            p2->startTurn();
            CHECK_THROWS(p2->build("Village",catan.getBoard(),48,48));
        }
        SUBCASE("Place in place not next to your road, not in first turn"){
            p1->startTurn();
            p1->build("Village",catan.getBoard(),5,5);
            p1->build("Road",catan.getBoard(),5,2);
            p1->build("Road",catan.getBoard(),2,6);
            p1->endTurn();
            p1->startTurn();
            Set<ResourceCard> set = Property("Village",1).getCost();
            p1->receive(set);
            CHECK_THROWS(p1->build("Village",catan.getBoard(),10,10));
        }
        SUBCASE("Place in place not 2 steps away from other Village"){
            p1->startTurn();
            p1->build("Village",catan.getBoard(),5,5);
            p1->endTurn();
            p2->startTurn();
            CHECK_THROWS(p2->build("Village",catan.getBoard(),2,2));
        }
    }
    SUBCASE("City"){
        SUBCASE("Place in the first turn"){
            p1->startTurn();
            CHECK_THROWS(p1->build("City",catan.getBoard(),5,5));

        }
        SUBCASE("Place in place that is not your village"){
            p1->startTurn();
            p1->build("Village",catan.getBoard(),5,5);
            p1->endTurn();
            p1->startTurn();
            CHECK_THROWS(p1->build("City",catan.getBoard(),8,8));
            // Check if building a City win points as expected
        }
    }
    SUBCASE("place property if is out of properties"){}
}

TEST_CASE("Check Trade with yourself"){
    p1->startTurn();
    Set<ResourceCard> set;
    Set<ResourceCard> set2;
    CHECK_THROWS(p1->trade(set,p1,set2));
}

TEST_CASE("Check Dice is 7 remove resources from player with under 7 cards"){
    Player *p1 = new Player("P1", 10);
    Player *p2 = new Player("P2", 20);
    Player *p3 = new Player("P3", 30);
    Catan catan = Catan(p1, p2, p3);
    p1->startTurn();
    Set<ResourceCard> set;set.add("Wool",6);
    Set<ResourceCard> remove;remove.add("Wool",2);
    p1->receive(set);
    CHECK_THROWS(p1->removeHalf(remove));
}

TEST_CASE("check Board"){}