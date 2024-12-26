#ifndef GAME_H
#define GAME_H

#include "Utility.h"
#include "PlayerInput.h"

class Game {
public:
    Game(std::istream& cin, std::ostream& cout);
    bool play();
private:
    const PlayerInput m_playerInput;
};

#endif