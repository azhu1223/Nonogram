#include "GameGeneratorDispatcher.h"
#include "Utility.h"
#include "GameGenerator.h"
#include "RandomGameGenerator.h"

#include <memory>

u_ptr<GameGenerator> GameGeneratorDispatcher::dispatch(const PlayerInput& playerInput, StartMenuResponse type) const {
    u_ptr<GameGenerator> res;

    switch (type) {
    case StartMenuResponse::RANDOM_GAME:
        res = std::make_unique<RandomGameGenerator>(playerInput);
    }

    return res;
}