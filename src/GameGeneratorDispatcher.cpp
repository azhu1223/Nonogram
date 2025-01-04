#include "GameGeneratorDispatcher.h"
#include "Utility.h"
#include "GameGenerator.h"
#include "RandomGameGenerator.h"
#include "LevelCreatorGameGenerator.h"

#include <memory>

u_ptr<GameGenerator> GameGeneratorDispatcher::dispatch(const PlayerInput& playerInput, StartMenuResponse type) const {
    u_ptr<GameGenerator> res;

    switch (type) {
    case StartMenuResponse::RANDOM_GAME:
        res = std::make_unique<RandomGameGenerator>(playerInput);
        break;
    case StartMenuResponse::MAKE_PUZZLE:
        res = std::make_unique<LevelCreatorGameGenerator>(playerInput);
        break;
    }

    return res;
}