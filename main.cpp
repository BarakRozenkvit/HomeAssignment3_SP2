#include "Player.hpp"
#include "Catan.hpp"
#include "Dice.hpp"
#include <iostream>


int main() {

    // Determine who playes first by rolling dices
    Player *p1 = new Player("amit", 10);
    Player *p2 = new Player("Yossi", 20);
    Player *p3 = new Player("Dana", 30);
    Catan catan = Catan(p1, p2, p3);
    bool isValid;

    //each player places two settelment and two roads and get resources
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

        Player* p = catan.nextPlayer();

        int chooseA;
        cout<<"Hi "<<p->getName()<<" it's your Turn! -> Choose an Action:\n\t0 - Roll Dice\n\t1 - Use a Development Card"<<endl;
        cout<<"Your'e Choice: ";cin>>chooseA;
        if(chooseA){
            int idx;
            cout<<"Choose idx of which number from development: "<<endl;
            while (1) {
                cin >> idx;
                string card = catan.flashDevelopmentCard(idx);
                if (card == "Knight"){

                    catan.flashKnight();
                }
                else if(card == "Monopoly"){
                    string desired_resource;
                    //input
                    catan.flashMonopoly(desired_resource);
                }
                else if(card == "Builder"){
                    int x1,x2,y1,y2;
                    //input

                    catan.flashBuilder(x1,y1,x2,y2);

                }
                else if(card == "WealthyYear"){

                    catan.flashWealthyYear();

                }
            }
        }
        else {
            int rand = Dice::roll();
            cout << "The random number is: " << rand << endl;
            if (rand == 7) {
                cout << "Time for player to take your staff" << endl;
            } else {
                for (int i = 0; i < 3; i++) {
                    catan.getResources(rand);
                    p->print();
                    p = catan.nextPlayer();
                }
            }

            int chooseB;
            bool onGoing = true;
            cout << "Hi " << p->getName()
                 << " it's your Turn! -> Choose an Action:\n\t1 - Trade\n\t2 - Draw a Development Card\n\t3 - Place Property\n"
                 << "\t4 - Use a Development Card\n\t5 - Exit" << endl;
            while (onGoing) {
                cout << "Your'e Choice: ";cin >> chooseB;
                cout << endl;

                switch (chooseB) {

                    case 1:

                        break;

                    case 2:


                        break;

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

                    case 4:


                        onGoing = false;
                        break;
                    case 5:
                        break;
                }
            }
        }




//                                input("1- Trade, 2-DevelopmentCard,3-Buy,4-Exit")
//                                switch(input){
//                                    case(1){
//                                        //Trade with who, what do i get, what i give?
//                                        break;
//                                    }
//                                    case(2){
//                                        // how much i have?
//                                        // what developmet card i use
//                                    }
//                                    case(3){
//                                        // what i build?
//                                        // where?
//                                        // is it legal?
//                                    }
//                                    case(4){
//                                        turn =0;
//                                        break;
//                                    }
//                                }
//                        }
//                }
//                checkWinner();
//                p++;
//                if(p=4){
//                    p=0;
//                }
//        }
        int g = 1;
    }
}
