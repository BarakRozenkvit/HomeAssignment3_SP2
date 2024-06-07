#include "Player.hpp"
#include "Catan.hpp"
#include "Dice.hpp"
#include "Set.hpp"
#include <iostream>

int main() {

    // Initial Game
    Player *p1 = new Player("Omriki", 10);
    Player *p2 = new Player("Momo", 20);
    Player *p3 = new Player("Omriki2", 30);
    Catan catan = Catan(p1,p2,p3);
//    catan.printGame();
    bool isValid;
    // each player places two Villages and two Roads and get Resources
    cout << "Welcome to Catan!!" << endl;
    for(int i=0;i<NUM_OF_PLAYERS;i++){
        catan.nextPlayer();
        int x;
        int y;
        catan.printGame("Initial Placement > 1 Village");
        cout << "x: ";
        isValid = false;
        while (!isValid) {
        std::cin >> x;
            isValid = catan.placeProperty("Village", x, x);
        }
        catan.printGame("Initial Placement > 1st Village > 1st Road");
        cout << "x y: ";
        isValid = false;
        while (!isValid) {
        std::cin >> x >> y;
            isValid = catan.placeProperty("Road", x, y);
        }
        catan.printGame("Initial Placement > 1st Village > 1st Road > 2nd Village");
        cout << "x: ";
        isValid = false;
        while (!isValid) {
        std::cin >> x;
            isValid = catan.placeProperty("Village", x, x);
        }
        catan.printGame("Initial Placement > 1st Village > 1st Road > 2nd Village > 2nd Road");
        cout << "x y: ";
        isValid = false;
        while (!isValid) {
        std::cin >> x >> y;
            isValid = catan.placeProperty("Road", x, y);
        }
        cout << catan.currentPlayer()->getName() << " Received: " << catan.getResources() <<endl;
        sleep(2);
    }

    while (1) {
        // Next player
        catan.nextPlayer();
        // Choose to roll a dice or use Development Card
        int useDevelopmentCard;
        int continueTurn = 1;

        while (continueTurn) {
            catan.printGame("Start Turn");
            cout << "Choose an Action:\n\t0 - Roll Dice\n\t1 - Use a Development Card\nYour'e Choice: ";
            cin >> useDevelopmentCard;
            switch (useDevelopmentCard) {
                //Use Development Card
                case 1: {
                    bool leave = true;
                    while(leave){
                        catan.printGame("Start Turn > Use Development Card");
                        cout << "Card Name: 1. Knight , 2. Builder, 3. Monopoly, 4. WealthyYear, 5. Exit" <<endl;
                        int num;
                        cin >> num;
                        switch (num) {
                            case 1:{
                                bool res = catan.useKnightCard();
                                if(res){
                                    continueTurn = 0;
                                    sleep(2);
                                }
                                else{
                                    cout << "No Knight Card!"<<endl;
                                    sleep(2);
                                }
                                break;
                            }
                            case 2:{
                                catan.printGame("Start Turn > Use Development Card > Builder Card");
                                int x1,y1,x2,y2;
                                cout << "First x y: ";
                                cin >> x1 >> y1;
                                cout << "Second x y: ";
                                cin >> x1 >> y2;
                                bool res = catan.useBuilderCard(x1,y1,x2,y2);
                                if(res){
                                    continueTurn = 0;
                                    sleep(2);
                                }
                                else{
                                    cout << "No Builder Card or Failed Build Road "<<endl;
                                    sleep(2);
                                }
                                break;

                            }
                            case 3:{
                                catan.printGame("Start Turn > Use Development Card > Monopoly Card");
                                cout << "Choose Resource: (Wheat,Wool,Iron,Brick,Wood)" <<endl;
                                string resource;
                                cin >> resource;
                                bool res = catan.useMonopolyCard(resource);
                                if(res){
                                    continueTurn = 0;
                                    sleep(2);
                                }
                                else{
                                    cout << "No Monopoly Card "<<endl;
                                    sleep(2);
                                }
                                break;
                            }
                            case 4:{
                                catan.printGame("Start Turn > Use Development Card > WealthyYear Card");
                                cout << "Choose First Resource: (Wheat,Wool,Iron,Brick,Wood)"<<endl;
                                string resource1;
                                cin >> resource1;
                                cout << "Choose Second Resource: (Wheat,Wool,Iron,Brick,Wood)" <<endl;
                                string resource2;
                                cin >> resource2;
                                bool res = catan.useWealthyYearCard(resource1,resource2);
                                if(res){
                                    continueTurn = 0;
                                    sleep(2);
                                }
                                else{
                                    cout << "No WhealthyYear Card "<<endl;
                                    sleep(2);
                                }
                                break;
                            }
                            case 5:{
                                leave = 0;
                                break;
                            }
                        }
                    }
                }
                // Roll Dice
                case 0: {
                    int rand = Dice::roll();
                    rand = 4;
                    catan.printGame("Start Turn > Dice Roll");
                    cout << "The Dice rolled: " << to_string(rand) << endl;

                    if (rand == 7) {
                        catan.printGame("Start Turn > Dice Roll > Got 7");
                        Set<ResourceCard> resources;
                        catan.nextPlayer();
                        for(int i=0;i<2;i++){
                            if(catan.currentPlayer()->getAmountResources() > 7){
                                Set<ResourceCard> yres;
                                int req = catan.currentPlayer()->getAmountResources()/2;string type;
                                int amount;
                                bool stillINDeal = true;
                                while (stillINDeal) {
                                    catan.printGame("Start Turn > Dice Roll > Got 7 > " + catan.currentPlayer()->getName() + "'s Resources Cut");
                                    cout << "Current Resources Cut (requested" <<to_string(req)<<"): " << yres << endl;
                                    cout << "0.Done , 1.Add to Cut, 2.remove From Resources Cut";
                                    int x;
                                    cin >> x;
                                    switch (x) {
                                        case 0: {
                                            if(yres.total() == req && catan.currentPlayer()->canPay(yres)){
                                                stillINDeal = false;
                                                cout << "Allowed" <<endl;
                                                sleep(2);
                                            }
                                            else{
                                                cout << "Not Allowed"<<endl;
                                            }
                                            break;
                                        }
                                        case 1: {
                                            catan.printGame("Start Turn > Dice Roll > Got 7 > " + catan.currentPlayer()->getName() +
                                                                    "'s Resources Cut > Add to Resources Cut");
                                            cout << "Current Resources Cut (requested" <<to_string(req)<<"): " << yres << endl;
                                            cout << "(Type Amount): ";
                                            cin >> type >> amount;
                                            yres.add(type, amount);
                                            break;
                                        }
                                        case 2: {
                                            catan.printGame("Start Turn > Dice Roll > Got 7 > " + catan.currentPlayer()->getName() +
                                                                    "'s Resources Cut > Remove From Resources Cut");
                                            cout << "Current Resources Cut (requested" <<to_string(req)<<"): " << yres << endl;
                                            cout << "(Type Amount): ";
                                            cin >> type >> amount;
                                            yres.remove(type, amount);
                                            break;
                                        }
                                    }
                                }
                                catan.currentPlayer()->pay(yres);
                                resources += yres;
                            }
                            else{
                                cout<<catan.currentPlayer()->getName() + " is saved from resource cut"<<endl;
                                sleep(2);
                            }
                            catan.nextPlayer();
                        }
                    }
                    else {
                        for (int i = 0; i < NUM_OF_PLAYERS; i++) {
                            cout << catan.currentPlayer()->getName() << " Received: " << catan.getResources() <<endl;
                            sleep(2);
                            catan.nextPlayer();
                        }
                    }

                    int chooseB;
                    bool mainLoop = true;
                    while (mainLoop) {
                        catan.printGame("Start Turn > Dice Roll > Home Menu");
                        cout<< "Choose an Action:\n\t1 - Trade\n\t2 - Draw a Development Card\n\t3 - Place Property\n\t4 - Use a Development Card\n\t5 - Exit\nYour'e Choice: ";
                        cin >> chooseB;
                        switch (chooseB) {
                            // Trade
                            case 1: {
                                Player* tradeWithP = nullptr;
                                while (1) {
                                    catan.printGame("Start Turn > Dice Roll > Home Menu > Trade");
                                    cout << "Trade with: 1." + p1->getName() + " 2." + p2->getName() + " 3." +p3->getName() << " 4.Exit"<<endl;
                                    int tradeWith;
                                    cin >> tradeWith;
                                    switch (tradeWith) {
                                        case 1: {
                                            tradeWithP = p1;
                                            break;
                                        }
                                        case 2:{
                                            tradeWithP = p2;
                                            break;

                                        }
                                        case 3:{
                                            tradeWithP = p3;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                if(tradeWithP == nullptr){
                                    break;
                                }
                                if(tradeWithP == catan.currentPlayer()){
                                    cout << "Cant Trade with yourself"<<endl;
                                    sleep(2);
                                    break;
                                }

                                Set<ResourceCard> MEresource;
                                Set<ResourceCard> Otherresource;
                                string type;
                                int amount;
                                bool stillINDeal = true;
                                while (stillINDeal) {
                                        catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + catan.currentPlayer()->getName() + "'s Trade");
                                        cout << "Current Trade: " << MEresource << endl;
                                        cout << "0.Done , 1.Add to Trade, 2.remove From Trade";
                                        int x;
                                        cin >> x;
                                        switch (x) {
                                            case 0: {
                                                stillINDeal = false;
                                                break;
                                            }
                                            case 1: {
                                                catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + catan.currentPlayer()->getName() +
                                                          "'s Trade > Add to Trade");
                                                cout << "Current Trade: " << MEresource << endl;
                                                cout << "(Type Amount): ";
                                                cin >> type >> amount;
                                                MEresource.add(type, amount);
                                                break;
                                            }
                                            case 2: {
                                                catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + catan.currentPlayer()->getName() +
                                                          "'s Trade > Remove From Trade");
                                                cout << "Current Trade: " << MEresource << endl;
                                                cout << "(Type Amount): ";
                                                cin >> type >> amount;
                                                MEresource.remove(type, amount);
                                                break;
                                            }
                                        }
                                    }
                                stillINDeal = true;
                                while (stillINDeal) {
                                    catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + tradeWithP->getName() + " Trade",tradeWithP);
                                    cout << "Current Trade: " << Otherresource << endl;
                                    cout << "0.Done , 1.Add to Trade, 2.remove From Trade";
                                    int y;
                                    cin >> y;
                                    switch (y) {
                                        case 0: {
                                            stillINDeal = false;
                                            break;
                                        }
                                        case 1: {
                                            catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + tradeWithP->getName() +
                                            "'s Trade > Add to Trade",tradeWithP);
                                            cout << "Current Trade: " << Otherresource << endl;
                                            cout << "(Type Amount): ";
                                            cin >> type >> amount;
                                            Otherresource.add(type, amount);
                                            break;
                                        }
                                        case 2: {
                                            catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + tradeWithP->getName() +
                                            "'s Trade > Remove From Trade",tradeWithP);
                                            cout << "Current Trade: " << Otherresource << endl;
                                            cout << "(Type Amount): ";
                                            cin >> type >> amount;
                                            Otherresource.remove(type, amount);
                                            break;
                                        }
                                    }
                                }
                                catan.printGame("Start Turn > Dice Roll > Home Menu > Trade > " + tradeWithP->getName() +
                                                " Trade > Trade Summary");
                                cout << catan.currentPlayer()->getName() + " Gives " <<MEresource<<endl;
                                cout << tradeWithP->getName() + " Gives " << Otherresource<<endl;
                                cout << "Accpeted? ";
                                int d;
                                cin >> d;
                                if(d && catan.currentPlayer()->canPay(MEresource) && tradeWithP->canPay(Otherresource)){
                                    catan.currentPlayer()->pay(MEresource);
                                    catan.currentPlayer()->receive(Otherresource);
                                    tradeWithP->pay(Otherresource);
                                    tradeWithP->receive(MEresource);
                                    cout<<"Trade Complete"<<endl;
                                    sleep(2);
                                }
                                else{
                                    cout<<"Trade Failed"<<endl;
                                    sleep(2);
                                }
                                break;
                            }

                                // Buy a development card
                            case 2: {
                                catan.printGame("Start Turn > Dice Roll > Home Menu > Draw Development Card");
                                bool res = catan.drawDevelopmentCard("d");
                                if(res){cout<<"Purchase Completed!"<<endl;}
                                else{cout<<"Purchase Failed - Insufficient Funds"<<endl;}
                                sleep(2);
                                break;
                            }
                                // Place a property
                            case 3: {
                                catan.printGame("Start Turn > Dice Roll > Home Menu > Place Property");
                                cout << "Choose an Action:\n\t1 - Road\n\t2 - Village\n\t3 - City\n\t4 - Exit\n";
                                int x;
                                int y;
                                int property;
                                cin >> property;
                                switch (property) {
                                    case 1:
                                        catan.printGame("Start Turn > Dice Roll > Home Menu > Place Property > Road");
                                        cout << "Where?\n";
                                        cin >> x >> y;
                                        catan.placeProperty("Road", x, y);
                                        break;
                                    case 2:
                                        catan.printGame("Start Turn > Dice Roll > Home Menu > Place Property > Village");
                                        cout << "Where?\n";
                                        std::cin >> x;
                                        catan.placeProperty("Village", x, x);
                                        break;
                                    case 3:
                                        catan.printGame("Start Turn > Dice Roll > Home Menu > Place Property > City");
                                        cout << "Where?\n";
                                        std::cin >> x;
                                        catan.placeProperty("City", x, x);
                                        break;
                                }
                                break;
                            }
                                // use development card and finish turn
                            case 4: {
                                bool leave = true;
                                while (leave) {
                                    catan.printGame("Start Turn > Dice Roll > Home Menu > Use Development Card");
                                    cout << "Card Name: 1. Knight , 2. Builder, 3. Monopoly, 4. WealthyYear, 5. Exit"
                                         << endl;
                                    int num;
                                    cin >> num;
                                    switch (num) {
                                        case 1: {
                                            bool res = catan.useKnightCard();
                                            if (res) {
                                                continueTurn = 0;
                                                sleep(2);
                                            } else {
                                                cout << "No Knight Card!" << endl;
                                                sleep(2);
                                            }
                                            break;
                                        }
                                        case 2: {
                                            catan.printGame(
                                                    "Start Turn > Dice Roll > Home Menu > Use Development Card > Builder Card");
                                            int x1, y1, x2, y2;
                                            cout << "First x y: ";
                                            cin >> x1 >> y1;
                                            cout << "Second x y: ";
                                            cin >> x1 >> y2;
                                            bool res = catan.useBuilderCard(x1, y1, x2, y2);
                                            if (res) {
                                                continueTurn = 0;
                                                sleep(2);
                                            } else {
                                                cout << "No Builder Card or Failed Build Road " << endl;
                                                sleep(2);
                                            }
                                            break;

                                        }
                                        case 3: {
                                            catan.printGame(
                                                    "Start Turn > Dice Roll > Home Menu > Use Development Card > Monopoly Card");
                                            cout << "Choose Resource: (Wheat,Wool,Iron,Brick,Wood)" << endl;
                                            string resource;
                                            cin >> resource;
                                            bool res = catan.useMonopolyCard(resource);
                                            if (res) {
                                                continueTurn = 0;
                                                sleep(2);
                                            } else {
                                                cout << "No Monopoly Card " << endl;
                                                sleep(2);
                                            }
                                            break;
                                        }
                                        case 4: {
                                            catan.printGame(
                                                    "Start Turn > Dice Roll > Home Menu > Use Development Card > WealthyYear Card");
                                            cout << "Choose First Resource: (Wheat,Wool,Iron,Brick,Wood)" << endl;
                                            string resource1;
                                            cin >> resource1;
                                            cout << "Choose Second Resource: (Wheat,Wool,Iron,Brick,Wood)" << endl;
                                            string resource2;
                                            cin >> resource2;
                                            bool res = catan.useWealthyYearCard(resource1, resource2);
                                            if (res) {
                                                continueTurn = 0;
                                                sleep(2);
                                            } else {
                                                cout << "No WhealthyYear Card " << endl;
                                                sleep(2);
                                            }
                                            break;
                                        }
                                        case 5: {
                                            leave = 0;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }

                            case 5: {
                                mainLoop = 0;
                                continueTurn = 0;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            // check win
        }
        if (catan.checkWin()) {
            cout <<"Win"<<endl;
            break;
            }
    }
}