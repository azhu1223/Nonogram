#ifndef BOARD_H
#define BOARD_H

#include "Utility.h"

#include <vector>

class Board {
public:
    Board(std::vector<std::vector<Cell>>* b);

    // Returns if the provided move is valid or not.
    bool fill(const FillDirection& d, const Point& start, const Point& end, const Cell& type);
    std::vector<std::vector<Cell>>* getVector();
private:
    int m_cols;
    int m_rows;
    std::vector<std::vector<Cell>>* m_board;
};

inline
std::vector<std::vector<Cell>>* Board::getVector() {
    return m_board;
}

#endif