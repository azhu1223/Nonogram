#include "GameGenerator.h"
#include "Utility.h"
#include "Game.h"

#include <istream>
#include <ostream>

class RandomGameGenerator : GameGenerator {
public:
    RandomGameGenerator(std::istream& cin, std::ostream& cout);
    virtual Result<u_ptr<Game>> generateGame() const;
private:
};