#ifndef START_MENU_SCENE_H
#define START_MENU_SCENE_H

#include "Scene.h"

#include <ostream>

class StartMenuScene : public Scene {
public:
    StartMenuScene(std::ostream& cout);
    virtual void display() const;
private:
};

#endif