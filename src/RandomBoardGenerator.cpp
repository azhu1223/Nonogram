#include "RandomBoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>
#include <random>

// Returns a result object that tells whether the returned pointer is valid or not.
Result<std::unique_ptr<Board>> RandomBoardGenerator::generateBoard(int rows, int columns, double probOfFilled) {
    if (rows <= 0 || columns <= 0 || probOfFilled < 0 || probOfFilled > 1) {
        return {nullptr, false};
    }

    std::vector<Cell> emptyRow(columns, Cell::NOTHING);
    std::unique_ptr<BoardData> boardData(new BoardData(rows, emptyRow));

    // Initialize random number generator from a uniform distribution.
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution distr(0.0, 1.0);

    for (auto &row : *boardData) {
        for (auto &cell : row) {
            if (distr(rng) < probOfFilled) {
                cell = Cell::FILLED;
            }
        }
    }

    return {std::unique_ptr<Board>(new Board(std::move(boardData))), true};
}