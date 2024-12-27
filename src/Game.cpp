#include "Game.h"
#include "Utility.h"
#include "PlayerInput.h"
#include "RandomBoardGenerator.h"
#include "Board.h"

#include <istream>
#include <ostream>
#include <string>
#include <random>
#include <utility>

Game::Game(std::istream& cin, std::ostream& cout) : m_cin(cin), m_cout(cout), 
    m_playerInput(new PlayerInput(m_cin, m_cout)) {}

bool Game::startNewRandomGame() {
    u_ptr<Settings> gameSettings = m_playerInput->getGameInitializationSettings();

    int rowSize = std::stoi((*gameSettings)[GameSetting::ROW_SIZE]);
    int colSize = std::stoi((*gameSettings)[GameSetting::COLUMN_SIZE]);
    double probFilled = std::stod((*gameSettings)[GameSetting::FILL_PROBABILITY]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    
    RandomBoardGenerator boardGenerator(probFilled, std::bind(distribution, gen));
    Result<s_ptr<Board>> answerBoardResult = boardGenerator.generateBoard(rowSize, colSize);

    if (!answerBoardResult.second) {
        return false;
    }

    m_answerBoard = answerBoardResult.first;

    m_gameplayBoard = s_ptr<Board>(new Board(rowSize, colSize));

    m_gameplayScene = u_ptr<GameplayScene>(new GameplayScene(m_cout, m_gameplayBoard, m_answerBoard->getHints()));

    return true;
}

bool Game::play() {
    while (!gameFinished()) {
        m_gameplayScene->display();

        Move move = m_playerInput->getMove(m_gameplayBoard->getNumRows(), m_gameplayBoard->getNumColumns());

        Action action = move.first;
        std::pair<Point, Point> startEnd = move.second;

        Result<Cell> fillCellResult = actionToCell(action);
        if (!fillCellResult.second) {
            //Handle quit and error
        }

        m_gameplayBoard->fill(startEnd.first, startEnd.second, fillCellResult.first);
    }

    return true;
}

Result<Cell> Game::actionToCell(const Action& a) const {
    Cell ret;
    bool valid = true;

    switch(a) {
    case Action::FILL:
        ret = Cell::FILLED;
        break;

    case Action::ELIMINATE:
        ret = Cell::ELIMINATED;
        break;
    
    case Action::TEST:
        ret = Cell::TEST;
        break;
    
    default:
        ret = Cell::DEFAULT;
        valid = false;
        break;
    }

    return {ret, valid};
}

bool Game::gameFinished() const {
    int numRows = m_gameplayBoard->getNumRows();
    int numCols = m_gameplayBoard->getNumColumns();

    bool ret = true;

    for (int i = 0; i < numRows && ret; i++) {
        const std::vector<Cell>& gameplayBoardRow = m_gameplayBoard->getRow(i);
        const std::vector<Cell>& answerBoardRow = m_answerBoard->getRow(i);

        for (int j = 0; j < numCols; j++) {
            if (!(gameplayBoardRow[j] == Cell::FILLED && answerBoardRow[j] == Cell::FILLED ||
                gameplayBoardRow[j] != Cell::FILLED && answerBoardRow[j] != Cell::FILLED)) {
                
                ret = false;
            }
        }
    }

    return ret;
}