#ifndef GAME_H
#define GAME_H

#include "Utility.h"
#include "PlayerInput.h"
#include "GameplayScene.h"

#include <istream>
#include <ostream>

class Game {
public:
    Game(std::istream& cin, std::ostream& cout);
    bool startNewRandomGame();
    bool play();
private:
    bool gameFinished() const;
    Result<Cell> actionToCell(const Action& a) const;
    std::istream& m_cin;
    std::ostream& m_cout;
    const u_ptr<PlayerInput> m_playerInput;
    s_ptr<Board> m_answerBoard;
    s_ptr<Board> m_gameplayBoard;
    u_ptr<GameplayScene> m_gameplayScene;
};

#endif