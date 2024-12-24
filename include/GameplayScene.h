#include "Scene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <string>

class GameplayScene : Scene {
public:
    GameplayScene(std::ostream& cout, s_ptr<Board> board, const std::vector<std::string>& hints);
    virtual void display();
private:
    std::string generateBoardDisplay();
    std::string generateHintDisplay();
    s_ptr<Board> m_board;
    
    const std::vector<std::string>& m_hints;
    const std::string m_horBorder;
    const size_t m_boardNumRow;
};