#include "Scene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>

class GameplayScene : Scene {
public:
    GameplayScene(std::ostream& cout, const Board& board);
    virtual void display();
private:
    const Board& m_board;
};