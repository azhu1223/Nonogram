#ifndef BOARD_GENERATOR_H
#define BOARD_GENERATOR_H

#include "Board.h"
#include "Utility.h"

#include <memory>

class BoardGenerator {
public:
    virtual Result<u_ptr<Board>> generateBoard(int rows, int columns, double probOfFilled) = 0;
};

#endif