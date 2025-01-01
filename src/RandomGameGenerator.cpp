#include "RandomGameGenerator.h"
#include "Utility.h"
#include "Game.h"

#include <memory>

RandomGameGenerator::RandomGameGenerator(const PlayerInput& playerInput) : GameGenerator(playerInput) {}

Result<u_ptr<Game>> RandomGameGenerator::generateGame() const {
    u_ptr<Game> newGame(new Game(getPlayerInput()));

    if (!newGame->startNewRandomGame()) {
        return {nullptr, false};
    }

    return {std::move(newGame), true};
}