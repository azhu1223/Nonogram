#include "Game.h"
#include "RandomGameGenerator.h"
#include "Utility.h"
#include "StartMenuScene.h"
#include "GameGeneratorDispatcher.h"

#include <iostream>

int main() {
    StartMenuScene startMenuScene(std::cout);
    PlayerInput playerInput(std::cin, std::cout);
    GameGeneratorDispatcher gameGeneratorDispatcher;

    bool keepPlaying = true;
    while (keepPlaying) {
        startMenuScene.display();

        StartMenuResponse startMenuOption = playerInput.getMainMenuResponse();

        u_ptr<GameGenerator> gameGenerator = gameGeneratorDispatcher.dispatch(playerInput, startMenuOption);

        Result<u_ptr<Game>> gameResult = gameGenerator->generateGame();

        if (!gameResult.second) {
            // Handle game creation error
        }

        keepPlaying = gameResult.first->play();
    }

    std::cout << "Exiting program.\n";

    return 0;
}