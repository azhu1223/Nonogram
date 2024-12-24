#include "GameplayScene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <string>
#include <sstream>
#include <vector>

GameplayScene::GameplayScene(std::ostream& cout, s_ptr<Board> board, const Hints& hints) : Scene(cout), m_board(board), m_hints(generateHints(hints)), 
    m_horBorder(1 + 2 * (m_board->getNumRows()), '-'), m_boardNumRow(m_board->getNumRows()) {}

void GameplayScene::display() {
    getCout() << generateBoardDisplay() << m_hints;
}

std::string GameplayScene::generateBoardDisplay() {
    std::stringstream boardStringStream;
    boardStringStream << m_horBorder << '\n';

    for (int i = 0; i < m_boardNumRow; i++) {
        const std::vector<Cell>& currentRow = m_board->getRow(i);

        boardStringStream << '|';
        for (Cell c : currentRow) {
            boardStringStream << (char) c << '|';
        }
        boardStringStream << '\n';
    }

    boardStringStream << m_horBorder << '\n';

    return boardStringStream.str();
}

std::string GameplayScene::generateHints(const Hints& hints) {
    const std::vector<std::vector<int>> row_hints = hints.first;
    const std::vector<std::vector<int>> col_hints = hints.second;

    std::stringstream hintStringStream;
    hintStringStream << "Row Hints:\n";

    int nRows = row_hints.size();
    for (int i = 0; i < nRows; i++) {
        hintStringStream << i << ": ";

        const std::vector<int> currentHintRow = row_hints[i];
        int nHints = currentHintRow.size();
        for (int j = 0; j < nHints; j++) {
            hintStringStream << currentHintRow[j] << ' ';
        }

        hintStringStream << '\n';
    }

    hintStringStream << "\nCol Hints:\n";

    int nCols = col_hints.size();
    for (int i = 0; i < nCols; i++) {
        hintStringStream << i << ": ";

        const std::vector<int> currentHintCol = col_hints[i];
        int nHints = currentHintCol.size();
        for (int j = 0; j < nHints; j++) {
            hintStringStream << currentHintCol[j] << ' ';
        }

        hintStringStream << '\n';
    }

    hintStringStream << '\n';

    return hintStringStream.str();
}