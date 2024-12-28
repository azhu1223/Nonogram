#include "StartMenuScene.h"
#include "Scene.h"

#include <ostream>

StartMenuScene::StartMenuScene(std::ostream& cout) : Scene(cout) {}

void StartMenuScene::display() const {
    getCout() << "Welcome to Nonogram!\n"
        << "Please select from:\n"
        << "(r)andom puzzle, (l)oad puzzle, (m)ake puzzle, or (c)ontinue game.\n";
}
