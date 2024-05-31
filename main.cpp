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
    bool isValid;

    // each player places two Villages and two Roads and get Resources
    for (int i = 0; i < 3; i++) {
        Player *p = catan.nextPlayer();
        int x;
        int y;
        std::cout <<"It's Player No. "<<i<< " -> "<<p->getName() << "'s Turn!" << endl;
        isValid = false;
        while (!isValid) {
            std::cout << "Choose Where to place the 1st Village" << endl;
            std::cin >> x;
            isValid = catan.placeProperty("Village", x, x);
        }
        isValid = false;
        while (!isValid) {
            std::cout << "Choose Where to place the 1st Road" << endl;
            std::cin >> x >> y;
            isValid = catan.placeProperty("Road", x, y);
        }
        isValid = false;
        while (!isValid) {
            std::cout << "Choose Where to place the 2nd Village" << endl;
            std::cin >> x;

            isValid = catan.placeProperty("Village", x, x);
        }
        isValid = false;
        while (!isValid) {
            std::cout << "Choose Where to place the 2nd Road" << endl;
            std::cin >> x >> y;
            isValid = catan.placeProperty("Road", x, y);
        }
        catan.getResources();
        p->print();
    }

    while (1) {
        // Next player
        Player *p = catan.nextPlayer();
        p->print();

        // Choose to roll a dice or use Development Card
        int chooseA;
        cout << "Hi " << p->getName()
             << " it's your Turn! -> Choose an Action:\n\t0 - Roll Dice\n\t1 - Use a Development Card" << endl;
        cout << "Your'e Choice: ";
        cin >> chooseA;
        if (chooseA) {
            int idx;
            cout << "Choose idx of which number from development: " << endl;
            while (1) {
                cin >> idx;
                string card = catan.flashDevelopmentCard(idx);
                if (card == "Knight") {
                    catan.flashKnight();
                } else if (card == "Monopoly") {
                    string desired_resource;
                    cout << "Choose desired resource which you take from others: " << endl;
                    cin >> desired_resource;
                    catan.flashMonopoly(desired_resource);
                } else if (card == "Builder") {
                    int x1, x2, y1, y2;
                    std::cout << "Choose Where to place the 1st Road" << endl;
                    std::cin >> x1 >> y1;
                    std::cout << "Choose Where to place the 2st Road" << endl;
                    std::cin >> x2 >> y2;
                    catan.flashBuilder(x1, y1, x2, y2);
                } else if (card == "WealthyYear") {
                    string resource1, resource2;
                    std::cout << "Choose 2 Resource to take from Bank (can be the same)" << endl;
                    cin >> resource1 >> resource2;
                    catan.flashWealthyYear(resource1, resource2);
                }
            }
        }
            // roll a dice
        else {
            int rand = Dice::roll();
            cout << "The random number is: " << rand << endl;
            // if 7 any players with more then 7 card need to dump half of them
            if (rand == 7) {
                cout << "Time for player to take your staff" << endl;
            } else {
                // if not gain resources
                for (int i = 0; i < 3; i++) {
                    catan.getResources(rand);
//                    p->print();
                    p = catan.nextPlayer();
                }
            }

            p->print();

            int chooseB;
            bool onGoing = true;
            cout << "Hi " << p->getName()
                 << " it's your Turn! -> Choose an Action:\n\t1 - Trade\n\t2 - Draw a Development Card\n\t3 - Place Property\n"
                 << "\t4 - Use a Development Card\n\t5 - Exit" << endl;
            while (onGoing) {
                cout << "Your'e Choice: ";
                cin >> chooseB;
                cout << endl;

                switch (chooseB) {
                    // Trade
                    case 1:
                        cout << "-- Trade Center --" << endl;
                        break;
                        // Buy a development card
                    case 2:
                        catan.drawDevelopmentCard();
                        break;
                        // Place a property
                    case 3:
                        int property;
                        int x;
                        int y;
                        bool isValid;
                        cout << "--- The Property Store ---" << endl;
                        std::cout
                                << "Choose What do you want place: \\n\\t1 - Road\\n\\t2 - Village\\n\\t3 - City\\n\"<<\"\\t4 - Exit"
                                << endl;
                        cout << "Your'e Choice: ";
                        std::cin >> property;
                        switch (property) {
                            case 1:
                                std::cout << "Where? ";
                                std::cin >> x >> y;
                                isValid = catan.placeProperty("Road", x, y);
                                break;
                            case 2:
                                std::cout << "Where? ";
                                std::cin >> x >> x;
                                isValid = catan.placeProperty("Village", x, x);
                                break;
                            case 3:
                                std::cout << "Where? ";
                                std::cin >> x;
                                isValid = catan.placeProperty("City", x, x);
                                break;
                        }
                        break;
                        // use development card and finish turn
                    case 4:
                        int idx;
                        cout << "Choose idx of which number from development: " << endl;
                        while (1) {
                            cin >> idx;
                            string card = catan.flashDevelopmentCard(idx);
                            if (card == "Knight") {
                                catan.flashKnight();
                            } else if (card == "Monopoly") {
                                string desired_resource;
                                cout << "Choose desired resource which you take from others: " << endl;
                                cin >> desired_resource;
                                catan.flashMonopoly(desired_resource);
                            } else if (card == "Builder") {
                                int x1, x2, y1, y2;
                                std::cout << "Choose Where to place the 1st Road" << endl;
                                std::cin >> x1 >> y1;
                                std::cout << "Choose Where to place the 2st Road" << endl;
                                std::cin >> x2 >> y2;
                                catan.flashBuilder(x1, y1, x2, y2);
                            } else if (card == "WealthyYear") {
                                string resource1, resource2;
                                std::cout << "Choose 2 Resource to take from Bank (can be the same)" << endl;
                                cin >> resource1 >> resource2;
                                catan.flashWealthyYear(resource1, resource2);
                            }
                            break;
                        }
                        onGoing = false;
                        break;
                        //exit
                    case 5:
                        onGoing = false;
                        break;
                }
            }
        }
    }    // check win
}
