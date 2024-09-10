#include "FakeBoardGenerator.h"
#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>

// Returns a board with the diagonal filled for testing purposes.
Result<std::unique_ptr<Board>> FakeBoardGenerator::generateBoard(int rows, int columns, double probOfFilled) {
    if (rows <= 0 || columns <= 0 || probOfFilled < 0 || probOfFilled > 1) {
        return {nullptr, false};
    }

    std::unique_ptr<BoardData> boardData(new BoardData());

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(i == j ? Cell::FILLED : Cell::NOTHING);
        }

        boardData->push_back(row);
    }

    return {std::unique_ptr<Board>(new Board(std::move(boardData))), true};
}