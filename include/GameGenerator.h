#ifndef GAME_GENERATOR_H
#define GAME_GENERATOR_H

#include "Utility.h"
#include "Game.h"

#include <istream>
#include <ostream>

class GameGenerator {
public:
    GameGenerator(std::istream& cin, std::ostream& cout);
    virtual Result<u_ptr<Game>> generateGame() const = 0;
    std::istream& getCin() const;
    std::ostream& getCout() const;
private:
    std::istream& m_cin;
    std::ostream& m_cout;
};

inline
GameGenerator::GameGenerator(std::istream& cin, std::ostream& cout) : m_cin(cin), m_cout(cout) {}

inline
std::istream& GameGenerator::getCin() const { return m_cin; }

inline
std::ostream& GameGenerator::getCout() const { return m_cout; }

#endif