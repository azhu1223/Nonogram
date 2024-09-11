#ifndef FAKE_BOARD_GENERATOR_H
#define FAKE_BOARD_GENERATOR_H

#include "BoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <memory>

class FakeBoardGenerator : BoardGenerator {
public:
    virtual Result<u_ptr<Board>> generateBoard(int rows, int columns, double probOfFilled);
};

#endif