#ifndef GAME_H
#define GAME_H

#include "Utility.h"
#include "PlayerInput.h"
#include "GameplayScene.h"

#include <istream>
#include <ostream>

class Game {
public:
    Game(const PlayerInput& playerInput);
    bool startNewRandomGame();
    bool play();
private:
    bool gameFinished() const;
    Result<Cell> actionToCell(const Action& a) const;
    s_ptr<Board> m_answerBoard;
    s_ptr<Board> m_gameplayBoard;
    u_ptr<GameplayScene> m_gameplayScene;

    const PlayerInput& m_playerInput;
};

#endif