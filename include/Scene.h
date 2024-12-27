#ifndef SCENE_H
#define SCENE_H

#include <ostream>

class Scene {
public:
    Scene(std::ostream& cout);
    virtual void display() = 0;
protected:
    std::ostream& getCout();
private:
    std::ostream& m_cout;
};

inline
Scene::Scene(std::ostream& cout) : m_cout(cout) {}

inline 
std::ostream& Scene::getCout() { return m_cout; }

#endif