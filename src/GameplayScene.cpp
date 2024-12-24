#include "GameplayScene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <string>
#include <sstream>
#include <vector>

GameplayScene::GameplayScene(std::ostream& cout, s_ptr<Board> board, const std::vector<std::string>& hints) : Scene(cout), m_board(board), m_hints(hints),
    m_horBorder(1 + 2 * (m_board->getNumRows()), '-'), m_boardNumRow(m_board->getNumRows()) {}

void GameplayScene::display() {
    getCout() << generateBoardDisplay() << generateHintDisplay();
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

std::string GameplayScene::generateHintDisplay() {

}