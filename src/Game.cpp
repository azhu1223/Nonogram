#include "Game.h"
#include "Utility.h"
#include "PlayerInput.h"
#include "RandomBoardGenerator.h"
#include "Board.h"

#include <istream>
#include <ostream>
#include <string>
#include <random>

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
    
}