#include "Game.h"
#include "RandomGameGenerator.h"
#include "Utility.h"
#include "StartMenuScene.h"

#include <iostream>

int main() {
    StartMenuScene startMenuScene(std::cout);
    PlayerInput playerInput(std::cin, std::cout);
    RandomGameGenerator randomGameGenerator(playerInput);

    bool keepPlaying = true;
    while (keepPlaying) {
        Result<u_ptr<Game>> gameResult = randomGameGenerator.generateGame();

        if (!gameResult.second) {
            // Handle game creation error
        }

        keepPlaying = gameResult.first->play();
    }

    std::cout << "Exiting program.\n";

    return 0;
}