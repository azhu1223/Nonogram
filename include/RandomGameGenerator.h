#include "GameGenerator.h"
#include "Utility.h"
#include "Game.h"
#include "PlayerInput.h"

class RandomGameGenerator : public GameGenerator {
public:
    RandomGameGenerator(const PlayerInput& playerInput);
    virtual Result<u_ptr<Game>> generateGame() const;
private:
};