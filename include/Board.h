#ifndef BOARD_H
#define BOARD_H

#include "Utility.h"

#include <vector>
#include <memory>

class Board {
public:
    Board(u_ptr<BoardData> b);
    Board(int numRows, int numCols);

    // Returns if the provided move is valid or not. Start and end must define a horizontal or vertical line.
    bool fill(const Point& start, const Point& end, const Cell& type);
    const std::vector<Cell> getRow(int row) const;
    const std::vector<Cell> getColumn(int column) const;
    const Hints getHints() const;

    int getNumRows() const;
    int getNumColumns() const;
private:
    const Hints generateHints() const;
    
    u_ptr<BoardData> m_board;
    int m_cols;
    int m_rows;
    const Hints m_hints;
};


inline
const std::vector<Cell> Board::getRow(int row) const {
    return (*m_board)[row];
}

inline
const std::vector<Cell> Board::getColumn(int column) const {
    std::vector<Cell> col;

    for (auto row : *m_board) {
        col.push_back(row[column]);
    }

    return col;
}

inline
int Board::getNumRows() const {
    return m_rows;
}

inline
int Board::getNumColumns() const {
    return m_cols;
}

inline 
const Hints Board::getHints() const {
    return m_hints;
}

#endif