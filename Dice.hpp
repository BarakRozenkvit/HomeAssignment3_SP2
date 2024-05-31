#include <cstdlib>
#include <iostream>

class Dice {

public:

    static int roll() {
        srand(time(0)); // Seed with current time (using for illustration)
        int random_number = rand() % 11; // Generate a random number between 0 and RAND_MAX
        return random_number + 2;
    }
};
