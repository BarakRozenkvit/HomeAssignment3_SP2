#include "Player.hpp"
#include "Catan.hpp"
#include "Dice.hpp"
#include <iostream>


int main() {

    // Initial Game
//    Player *p1 = new Player("amit", 10);
//    Player *p2 = new Player("Yossi", 20);
//    Player *p3 = new Player("Dana", 30);
    Catan catan = Catan(new Player("amit", 10),
                        new Player("Yossi", 20),
                        new Player("Dana", 30));
//    catan.printGame();
    bool isValid;

    // each player places two Villages and two Roads and get Resources
        Player *p = catan.nextPlayer();
        catan.printGame("Welcome to Catan");
        int x;
        int y;
        std::cout <<"It's Player No. "<< " -> "<<p->getName() << "'s Turn!" << endl;
        isValid = false;
        while (!isValid) {
            catan.printGame("Choose Where to place the 1st Village");
//            std::cin >> x;
            isValid = catan.placeProperty("Village", 48, 48);
        }
        isValid = false;
        while (!isValid) {
            catan.printGame("Choose Where to place the 1st Road");
//            std::cin >> x >> y;
            isValid = catan.placeProperty("Road", 48, 44);
        }
        isValid = false;
        while (!isValid) {
            catan.printGame("Choose Where to place the 2nd Village");
//            std::cin >> x;

            isValid = catan.placeProperty("Village", 30, 30);
        }
        isValid = false;
        while (!isValid) {
            catan.printGame("Choose Where to place the 2nd Road");
//            std::cin >> x >> y;
            isValid = catan.placeProperty("Road", 30, 36);
        }
        catan.getResources();
    p = catan.nextPlayer();
//    int x;
//    int y;
    std::cout <<"It's Player No. "<< " -> "<<p->getName() << "'s Turn!" << endl;
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 1st Village");
//        std::cin >> x;
        isValid = catan.placeProperty("Village", 14, 14);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 1st Road");
//        std::cin >> x >> y;
        isValid = catan.placeProperty("Road", 14, 10);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 2nd Village");
//        std::cin >> x;
        isValid = catan.placeProperty("Village", 13, 13);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 2nd Road");
//        std::cin >> x >> y;
        isValid = catan.placeProperty("Road", 13, 8);
    }
    catan.getResources();
    p = catan.nextPlayer();
//    int y;
    std::cout <<"It's Player No. "<< " -> "<<p->getName() << "'s Turn!" << endl;
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 1st Village");
//        std::cin >> x;
        isValid = catan.placeProperty("Village", 5, 5);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 1st Road");
//        std::cin >> x >> y;
        isValid = catan.placeProperty("Road", 5, 2);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 2nd Village");
//        std::cin >> x;
        isValid = catan.placeProperty("Village", 6, 6);
    }
    isValid = false;
    while (!isValid) {
        catan.printGame("Choose Where to place the 2nd Road");
//        std::cin >> x >> y;
        isValid = catan.placeProperty("Road", 6, 2);
        catan.printGame("");
    }
    catan.getResources();
    catan.printGame("");

    while (1) {
        // Next player
        Player *p = catan.nextPlayer();
        // Choose to roll a dice or use Development Card
        int useDevelopmentCard;
        int continueTurn = 1;

        catan.printGame("Hi " + p->getName() + " it's your Turn! -> Choose an Action:\n\t0 - Roll Dice\n\t1 - Use a Development Card\nYour'e Choice: ");
        cin >> useDevelopmentCard;
        if (useDevelopmentCard) {
            int index;
            catan.printGame("Choose a Development Card to Use:\nYour'e Choice: ");
            cin >> index;
            bool res = catan.useDevelopmentCard(index);
            if(res){
                continueTurn = 0;
                }
            }

        if(continueTurn) {
            int rand = Dice::roll();
            catan.printGame("The random number is: " + to_string(rand));

            if (rand == 7) {
                catan.printGame("Time for player to take your staff");
            }
            else {
                for (int i = 0; i < 3; i++) {
                    catan.getResources(rand);
                    p = catan.nextPlayer();
                }
            }

            int chooseB;
            bool onGoing = true;
            while (onGoing) {
                catan.printGame("Hi " + p->getName() + " it's your Turn! -> Choose an Action:\n\t1 - Trade\n\t2 - Draw a Development Card\n\t3 - Place Property\n\t4 - Use a Development Card\n\t5 - Exit\nYour'e Choice: ");
                cin >> chooseB;
                switch (chooseB) {
                    // Trade
                    case 1:
                        catan.printGame("Trade Center");
                        break;
                    // Buy a development card
                    case 2:
                        catan.printGame("Draw Development Card");
                        catan.drawDevelopmentCard();
                        break;
                    // Place a property
                    case 3:
                        int property;
                        int x;
                        int y;
                        bool isValid;
                        catan.printGame("--- The Property Store ---\nChoose What do you want place: \\n\\t1 - Road\\n\\t2 - Village\\n\\t3 - City\\n\"<<\"\\t4 - Exit\nYour'e Choice: ");
                        cin >> property;
                        switch (property) {
                                cout << "Where? ";
                            case 1:
                                cin >> x >> y;
                                catan.placeProperty("Road", x, y);
                                break;
                            case 2:
                                std::cin >> x;
                                catan.placeProperty("Village", x, x);
                                break;
                            case 3:
                                std::cin >> x;
                                catan.placeProperty("City", x, x);
                                break;
                        }
                        break;
                    // use development card and finish turn
                    case 4:
                        int idx;
                        cout << "Choose idx of which number from development: " << endl;
                        while (1) {
                            cin >> idx;
                            bool res = catan.useDevelopmentCard(idx);
                            if (res) { break; }
                            break;
                        }
                        onGoing = false;
                        break;
                    //Exit
                    case 5:
                        onGoing = false;
                        break;
                }
            }
        }
    }    // check win
}
