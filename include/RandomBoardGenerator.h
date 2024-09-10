#ifndef RANDOM_BOARD_GENERATOR_H
#define RANDOM_BOARD_GENERATOR_H

#include "BoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <memory>

class RandomBoardGenerator : BoardGenerator {
public:
    virtual Result<std::unique_ptr<Board>> generateBoard(int rows, int columns, double probOfFilled) = 0;
};

#endif