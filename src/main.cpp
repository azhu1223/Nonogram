#include "Game.h"
#include "RandomGameGenerator.h"
#include "Utility.h"

#include <iostream>

int main() {
    RandomGameGenerator randomGameGenerator(std::cin, std::cout);

    bool keepPlaying = true;
    while (keepPlaying) {
        Result<u_ptr<Game>> gameResult = randomGameGenerator.generateGame();

        if (!gameResult.second) {
            // Handle game creation error
        }

        gameResult.first->play();

        keepPlaying = false;
    }

    std::cout << "Exiting program.\n";

    return 0;
}