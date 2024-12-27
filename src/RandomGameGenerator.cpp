#include "RandomGameGenerator.h"
#include "Utility.h"
#include "Game.h"

#include <memory>

RandomGameGenerator::RandomGameGenerator(std::istream& cin, std::ostream& cout) : GameGenerator(cin, cout) {}

Result<u_ptr<Game>> RandomGameGenerator::generateGame() const {
    u_ptr<Game> newGame(new Game(getCin(), getCout()));

    if (!newGame->startNewRandomGame()) {
        return {nullptr, false};
    }

    return {std::move(newGame), true};
}