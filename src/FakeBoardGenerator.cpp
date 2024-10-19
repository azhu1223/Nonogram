#include "FakeBoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <vector>
#include <functional>

// Returns a board with the diagonal filled for testing purposes.
Result<u_ptr<Board>> FakeBoardGenerator::generateBoard(int rows, int columns, double probOfFilled, std::function<double()> rng) {
    if (rows <= 0 || columns <= 0 || probOfFilled < 0 || probOfFilled > 1) {
        return {nullptr, false};
    }

    u_ptr<BoardData> boardData(new BoardData());

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(i == j ? Cell::FILLED : Cell::ELIMINATED);
        }

        boardData->push_back(row);
    }

    return {u_ptr<Board>(new Board(std::move(boardData))), true};
}