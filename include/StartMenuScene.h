#ifndef START_MENU_SCENE_H
#define START_MENU_SCENE_H

#include "Scene.h"

#include <ostream>

class StartMenuScene : Scene {
public:
    StartMenuScene(std::ostream& cout);
    virtual void display() const;
private:
};

#endif