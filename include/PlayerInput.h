#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "Utility.h"
#include "Board.h"

#include <ostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <utility>

class PlayerInput {
public:
    PlayerInput(std::istream& cin, std::ostream& cout);
    u_ptr<Settings> getGameInitializationSettings();
    Move getMove(const Board& board);

private:
    bool validIntegralAnswer(std::string s);
    bool validProbAnswer(std::string s);
    Action charToAction(char c);
    Result<Point> convertStringToPoint(const std::string& s);
    std::istream& m_cin;
    std::ostream& m_cout;
};

#endif