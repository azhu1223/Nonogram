#include "GameGeneratorDispatcher.h"
#include "Utility.h"
#include "GameGenerator.h"
#include "RandomGameGenerator.h"

u_ptr<GameGenerator> GameGeneratorDispatcher::dispatch(const PlayerInput& playerInput, MainMenuResponse type) const {
    u_ptr<GameGenerator> res;

    switch (type) {
    case MainMenuResponse::RANDOM_GAME:
        res = new RandomBoardGenerator(playerInput);
    }
}