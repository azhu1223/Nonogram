#ifndef GAME_GENERATOR_DISPATCHER_H
#define GAME_GENERATOR_DISPATCHER_H

#include "GameGenerator.h"
#include "RandomBoardGenerator.h"
#include "Utility.h"

class GameGeneratorDispatcher {
public:
    u_ptr<GameGenerator> dispatch(const PlayerInput& playerInput, MainMenuResponse type) const;
};

#endif