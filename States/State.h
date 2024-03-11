/*
States are the different "states" the game can be in. For example, the main menu, the game itself, the pause menu, etc.

Each state has its own update and draw functions. These states are managed by the StateManager class, which is a singleton.
The StateManager class is responsible for updating and drawing the current state, as well as switching between states.
*/

#pragma once

#include "Handler.h"
#include "ofMain.h"
#include <memory>

enum StateName {
    UNKNOWN,
    TITLE_SCREEN,
    GAME,
    PAUSE,
    GAME_OVER,
};

class State {

private:
    bool finished = false; // Whether or not the state is finished and should be switched
    StateName nextState;   // The next state to switch to

protected:
    string musicFileName;        // The music to play for this state
    shared_ptr<Handler> handler; // The handler for the game

public:
    State(shared_ptr<Handler> handler) { this->handler = handler; }

    // Required functions
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void keyPressed(int key) = 0;
    virtual void reset() = 0; // This is called when the state is reset

    // Optional functions
    virtual void keyReleased(int key){};
    virtual void mouseMoved(int x, int y){};
    virtual void mouseDragged(int x, int y, int button){};
    virtual void mousePressed(int x, int y, int button){};
    virtual void mouseReleased(int x, int y, int button){};

    bool isFinished() { return finished; }
    void setFinished(bool finished) { this->finished = finished; }

    StateName getNextState() { return nextState; }
    void setNextState(StateName nextState) { this->nextState = nextState; }

    string getMusicFileName() { return musicFileName; }
};