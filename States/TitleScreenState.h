#pragma once

#include "State.h"
#include <memory>

class TitleScreenState : public State {

private:
    shared_ptr<Animation> titleScreenAnimation;

public:
    TitleScreenState(shared_ptr<Handler> handler) : State(handler) { this->reset(); }
    void update();
    void draw();
    void reset();
    void keyPressed(int key);
    void keyReleased(int key);
};