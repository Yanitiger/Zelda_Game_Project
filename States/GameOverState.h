#pragma once

#include "State.h"
#include <memory>

class GameOverState : public State{
public:
    GameOverState(shared_ptr<Handler> handler) : State(handler) { this->reset(); }
    void update();
    void draw();
    void reset();
    void keyPressed(int key);
    void keyReleased(int key);
    ofImage screen;
    ofImage heart;
    int option;
};