#include "LevelCreatorGameGenerator.h"
#include "Utility.h"

LevelCreatorGameGenerator::LevelCreatorGameGenerator(const PlayerInput& playerInput) : GameGenerator(playerInput) {}

Result<u_ptr<Game>> LevelCreatorGameGenerator::generateGame() const {
    return {nullptr, false};
}