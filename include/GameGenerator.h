#ifndef GAME_GENERATOR_H
#define GAME_GENERATOR_H

#include "Utility.h"
#include "Game.h"
#include "PlayerInput.h"

#include <istream>
#include <ostream>

class GameGenerator {
public:
    GameGenerator(const PlayerInput& playerInput);
    virtual Result<u_ptr<Game>> generateGame() const = 0;
    std::istream& getCin() const;
    std::ostream& getCout() const;
    const PlayerInput& getPlayerInput() const;
private:
    const PlayerInput& m_playerInput;
};

inline
GameGenerator::GameGenerator(const PlayerInput& playerInput) : m_playerInput(playerInput){}

inline
std::istream& GameGenerator::getCin() const { return m_playerInput.getCin(); }

inline
std::ostream& GameGenerator::getCout() const { return m_playerInput.getCout(); }

inline
const PlayerInput& GameGenerator::getPlayerInput() const { return m_playerInput; }

#endif