#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include "Scene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <string>

class GameplayScene : Scene {
public:
    GameplayScene(std::ostream& cout, s_ptr<Board> board, const Hints& hints);
    virtual void display();
private:
    std::string generateBoardDisplay();
    std::string generateHints(const Hints& hints);
    s_ptr<Board> m_board;
    
    const std::string& m_hints;
    const std::string m_horBorder;
    const size_t m_boardNumRow;
};

#endif