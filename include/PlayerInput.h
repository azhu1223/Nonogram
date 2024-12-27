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
    u_ptr<Settings> getGameInitializationSettings() const;
    Move getMove(const Board& board) const;

private:
    bool validIntegralAnswer(std::string s) const;
    bool validProbAnswer(std::string s) const;
    Action charToAction(char c) const;
    Result<Point> convertStringToPoint(const std::string& s) const;
    std::istream& m_cin;
    std::ostream& m_cout;
};

#endif