#include "RandomBoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>
#include <random>

RandomBoardGenerator::RandomBoardGenerator(u_ptr<std::mt19937> rng, u_ptr<std::uniform_real_distribution<double>> distr) : BoardGenerator() {
    m_rng = std::move(rng);
    m_distr = std::move(distr);
}

// Returns a result object that tells whether the returned pointer is valid or not.
Result<u_ptr<Board>> RandomBoardGenerator::generateBoard(int rows, int columns, double probOfFilled) {
    if (rows <= 0 || columns <= 0 || probOfFilled < 0 || probOfFilled > 1) {
        return {nullptr, false};
    }

    std::vector<Cell> emptyRow(columns, Cell::NOTHING);
    u_ptr<BoardData> boardData(new BoardData(rows, emptyRow));

    // Initialize random number generator from a uniform distribution.

    for (auto &row : *boardData) {
        for (auto &cell : row) {
            if ((*m_distr)(*m_rng) < probOfFilled) {
                cell = Cell::FILLED;
            }
        }
    }

    return {u_ptr<Board>(new Board(std::move(boardData))), true};
}