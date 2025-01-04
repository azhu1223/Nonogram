#ifndef LEVEL_CREATOR_GAME_GENERATOR
#define LEVEL_CREATOR_GAME_GENERATOR

#include "GameGenerator.h"
#include "Utility.h"

class LevelCreatorGameGenerator : public GameGenerator {
    LevelCreatorGameGenerator(const PlayerInput& playerInput);
    virtual Result<u_ptr<Game>> generateGame() const;
};

#endif
