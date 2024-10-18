#include "RandomBoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>
#include <random>
#include <functional>
#include <iostream>

RandomBoardGenerator::RandomBoardGenerator(double probOfFilled, std::function<double()> rng) : BoardGenerator() {
    m_probOfFilled = probOfFilled;
    m_rng = rng;
}

// Returns a result object that tells whether the returned pointer is valid or not.
Result<u_ptr<Board>> RandomBoardGenerator::generateBoard(int rows, int columns) {
    if (rows <= 0 || columns <= 0 || m_probOfFilled < 0 || m_probOfFilled > 1) {
        return {nullptr, false};
    }

    // Intialize empty board vector
    u_ptr<BoardData> boardData(new BoardData(rows));

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row(columns, Cell::FILLED);

        // Fill in each column according to RNG
        for (Cell &cell : row) {
            if (m_rng() < m_probOfFilled) {
                cell = Cell::ELIMINATED;
            }
        }

        (*boardData)[i].swap(row);
    }

    return {u_ptr<Board>(new Board(std::move(boardData))), true};
}