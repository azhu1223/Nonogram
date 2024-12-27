#include "Board.h"
#include "Utility.h"

#include <vector>
#include <memory>
#include <utility>

Board::Board(u_ptr<BoardData> b) : m_board(std::move(b)), m_rows(m_board->size()), m_cols((*m_board)[0].size()), m_hints(generateHints()) {}

Board::Board(int numRows, int numCols) : m_rows(numRows), m_cols(numCols) {
    const std::vector<Cell> emptyRow = std::vector<Cell>(m_cols, Cell::DEFAULT);
    m_board = u_ptr<BoardData>(new BoardData(m_rows, emptyRow));
}

bool Board::fill(const Point& start, const Point& end, const Cell& type) {
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

    FillDirection d;
    if (startRow == endRow) {
        if (startCol == endCol) {
            d = FillDirection::CELL;
        }

        else {
            d = FillDirection::ROW;
        }
    }

    else if (startCol == endCol) {
        d = FillDirection::COLUMN;
    }

    else {
        return false;
    }

    switch(d) {
    case FillDirection::ROW:
        if (startRow != endRow) {
            return false;
        }

        for (int i = startCol; i <= endCol; i++) {
            Cell& currentCell = (*m_board)[startRow][i];

            // If the current cell is empty or holds the TEST cell, replace the characters with the new value.
            if (currentCell == Cell::DEFAULT || currentCell == Cell::TEST) {
                currentCell = type;
            }
        }

        break;

    case FillDirection::COLUMN:
        if (startCol != endCol) {
            return false;
        }

        for (int i = startRow; i <= endRow; i++) {
            Cell& currentCell = (*m_board)[i][startCol];

            // If the current cell is empty or holds the TEST cell, replace the characters with the new value.
            if (currentCell == Cell::DEFAULT || currentCell == Cell::TEST) {
                currentCell = type;
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

const Hints Board::generateHints() const {
    std::vector<std::vector<int>> row_hints(m_rows);
    std::vector<std::vector<int>> col_hints(m_cols);

    std::vector<int> col_tallies(m_cols, 0);

    int lastColIndex = m_cols - 1;

    for (int i = 0; i < m_rows; i++) {
        int row_tally = 0;
        
        const std::vector<Cell>& currentRow = (*m_board)[i];
        for (int j = 0; j < m_cols; j++) {
            const Cell& currentCell = currentRow[j];

            if (currentCell == Cell::DEFAULT) {
                if (row_tally > 0) {
                    row_hints[i].push_back(row_tally);
                    row_tally = 0;
                }

                if (col_tallies[j] > 0) {
                    col_hints[j].push_back(col_tallies[j]);
                    col_tallies[j] = 0;
                }
            }

            else {
                row_tally++;
                col_tallies[j]++;
            }
        }

        if (row_tally > 0) {
            row_hints[i].push_back(row_tally);
        }
    }

    for (int i = 0; i < m_cols; i++) {
        if (col_tallies[i] > 0) {
            col_hints[i].push_back(col_tallies[i]);
        }
    }

    return {row_hints, col_hints};
}