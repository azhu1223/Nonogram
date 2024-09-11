#ifndef RANDOM_BOARD_GENERATOR_H
#define RANDOM_BOARD_GENERATOR_H

#include "BoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <memory>
#include <random>

class RandomBoardGenerator : BoardGenerator {
public:
    RandomBoardGenerator(u_ptr<std::mt19937> rng, u_ptr<std::uniform_real_distribution<double>> distr);
    virtual Result<u_ptr<Board>> generateBoard(int rows, int columns, double probOfFilled);
private:
    u_ptr<std::mt19937> m_rng; 
    u_ptr<std::uniform_real_distribution<double>> m_distr;
};

#endif