#include "Catan.hpp"
#include "Dice.hpp"

int main(){
    // Create Game
    Player *p1 = new Player("Omri", 10);
    Player *p2 = new Player("Barak", 20);
    Player *p3 = new Player("Haim",30);
    Catan catan = Catan(p1,p2,p3);
    catan.nextPlayer();

    // Omri Turn
    catan.placeProperty("Village", 23, 23);
    catan.placeProperty("Road",23,29);
    catan.placeProperty("Village", 14, 14);
    catan.placeProperty("Road",14,9);
    catan.getResources(); //Omri: Wood 1 Wheat 1 Wool 2 Iron 2
    catan.nextPlayer();
    // Barak Turn
    catan.placeProperty("Village",45,45);
    catan.placeProperty("Road",45,41);
    catan.placeProperty("Village",22,22);
    catan.placeProperty("Road",41,36);
    catan.getResources(); //Barak: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 1
    catan.nextPlayer();
    // Haim Turn
    catan.placeProperty("Village",39,39);
    catan.placeProperty("Road",39,43);
    catan.placeProperty("Village",47,47);
    catan.placeProperty("Road",47,43);
    catan.getResources(); //Haim: Brick 1 Wheat 1 Wood 2
    catan.nextPlayer();

    // Game Begin
    // Omri Turn: Wood 1 Wheat 1 Wool 2 Iron 2
    int rand = 8;
    catan.getResources(rand); // Omri got nothing: Wood 1 Wheat 1 Wool 2 Iron 2
    catan.nextPlayer();
    catan.getResources(rand); // Barak got Wool 1: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    catan.nextPlayer();
    catan.getResources(rand); // Haim got Brick 1: Brick 2 Wheat 1 Wood 2
    catan.nextPlayer();

    // Omri: Wood 1 Wheat 1 Wool 2 Iron 2
    catan.drawDevelopmentCard("WinningPoints");// Omri got 3 winPoints: Wood 1 Wool 1 Iron 1
    catan.nextPlayer();

    // Barak: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    rand = 9;
    catan.getResources(rand); // Barak got nothing: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    catan.nextPlayer();
    catan.getResources(rand); // Haim got nothing: Brick 2 Wheat 1 Wood 2
    catan.nextPlayer();
    catan.getResources(rand); // Omri got Wool 1: Wood 1 Wool 2 Iron 1
    catan.nextPlayer();

    // Barak: Iron 1 Wood 1 Brick 1 Wheat 2 Wool 2
    catan.placeProperty("Road",22,28); // Barak Bank: Iron 1 Wheat 2 Wool 2









}