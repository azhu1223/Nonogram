#ifndef RANDOM_BOARD_GENERATOR_H
#define RANDOM_BOARD_GENERATOR_H

#include "BoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <memory>
#include <random>
#include <functional>

class RandomBoardGenerator : public BoardGenerator {
public:
    RandomBoardGenerator(double probOfFilled, std::function<double()> rng);
    virtual Result<s_ptr<Board>> generateBoard(int rows, int columns) const;
private:
    double m_probOfFilled;
    std::function<double()> m_rng;
};

#endif