#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>
#include <utility>

Board::Board(std::unique_ptr<std::vector<std::vector<Cell>>> b) {
    m_board = std::move(b);
    m_rows = m_board->size();
    m_cols = (*m_board)[0].size();
}

bool Board::fill(const FillDirection& d, const Point& start, const Point& end, const Cell& type) {
    int startRow = start.first;
    int startCol = start.second;
    int endRow = end.first;
    int endCol = end.second;

    if (startRow < 0 || startRow >= m_rows) {
        return false;
    }

    if (startCol < 0 || startCol >= m_cols) {
        return false;
    }

    switch(d) {
    case FillDirection::ROW:
        if (startRow != endRow) {
            return false;
        }

        for (int i = startCol; i <= endCol; i++) {
            Cell* currentCell = &((*m_board)[startRow][i]);

            // If the current cell is empty or holds the TEST cell, replace the characters with the new value.
            if (*currentCell == Cell::EMPTY || *currentCell == Cell::TEST) {
                *currentCell = type;
            }
        }

        break;

    case FillDirection::COLUMN:
        if (startCol != endCol) {
            return false;
        }

        for (int i = startRow; i <= endRow; i++) {
            Cell* currentCell = &((*m_board)[i][startCol]);

            // If the current cell is empty or holds the TEST cell, replace the characters with the new value.
            if (*currentCell == Cell::EMPTY || *currentCell == Cell::TEST) {
                *currentCell = type;
            }
        }

        break;
    
    case FillDirection::CELL:
        if (!(startRow == endRow && startCol == endCol)) {
            return false;
        }

        (*m_board)[startRow][startCol] = type;

        break;
    }

    return true;
}