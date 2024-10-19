#include "GameplayScene.h"
#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <string>

GameplayScene::GameplayScene(std::ostream& cout, const Board& board) : Scene(cout), m_board(board) {}

void GameplayScene::display() {
    
}