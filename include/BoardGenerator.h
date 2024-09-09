#include "Board.h"

#include <memory>

class BoardGenerator {
public:
    virtual std::unique_ptr<Board> generateBoard(int rows, int columns, double probOfFilled) = 0;
};