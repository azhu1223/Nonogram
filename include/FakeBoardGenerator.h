#ifndef FAKE_BOARD_GENERATOR_H
#define FAKE_BOARD_GENERATOR_H

#include "BoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <functional>

class FakeBoardGenerator : public BoardGenerator {
public:
    virtual Result<s_ptr<Board>> generateBoard(int rows, int columns) const;
};

#endif