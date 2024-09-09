#ifndef BOARD_H
#define BOARD_H

#include "Utility.h"

#include <vector>
#include <memory>

class Board {
public:
    Board(std::unique_ptr<std::vector<std::vector<Cell>>> b);

    // Returns if the provided move is valid or not.
    bool fill(const FillDirection& d, const Point& start, const Point& end, const Cell& type);

    std::vector<Cell> getRow(int row);

    std::vector<Cell> getColumn(int column);
private:
    int m_cols;
    int m_rows;
    std::unique_ptr<std::vector<std::vector<Cell>>> m_board;
};

inline
std::vector<Cell> Board::getRow(int row) {
    return (*m_board)[row];
}

inline
std::vector<Cell> Board::getColumn(int column) {
    std::vector<Cell> col;

    for (auto row : *m_board) {
        col.push_back(row[column]);
    }

    return col;
}

#endif