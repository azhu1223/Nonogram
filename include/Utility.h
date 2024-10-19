/*
Holds constants and other useful constructs used throughout the program.
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>

// Cell::REVEALED represents a REVEALED in cell. Cell::DEFAULT represents a cell that has not been modified yet. /
// Cell::ELIMINATED represents a cell that has been determined to be empty. Cell::TEST represents a cell that /
// is tentatively filled for testing.
enum class Cell {
    FILLED = '0',
    DEFAULT = '.',
    ELIMINATED = 'x',
    TEST = '?'
};

enum class Action {
    FILL,
    ELIMINATE,
    TEST,
    QUIT,
    ERROR
};

enum class FillDirection {
    ROW,
    COLUMN,
    CELL
};

enum class GameSetting {
    ROW_SIZE,
    COLUMN_SIZE,
    FILL_PROBABILITY
};

using Point = std::pair<int, int>;

using BoardData = std::vector<std::vector<Cell>>;

using Settings = std::unordered_map<GameSetting, std::string>;

using Move = std::pair<Action, std::pair<Point, Point>>;

template <typename T>
using Result = std::pair<T, bool>;

template <typename T>
using u_ptr = std::unique_ptr<T>;

#endif