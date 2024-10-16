#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "Utility.h"

#include <ostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <utility>

class PlayerInput {
public:
    PlayerInput(std::istream& cin, std::ostream& cout);
    u_ptr<std::unordered_map<Setting, std::string>> getGameInitializationSettings();
    std::vector<std::string> getMove();

private:
    bool validIntegralAnswer(std::string s);
    bool validProbAnswer(std::string s);
    std::istream& m_cin;
    std::ostream& m_cout;
};

#endif