#pragma once

#include "GameOverState.h"
#include "GameState.h"
#include "Handler.h"
#include "State.h"
#include "TitleScreenState.h"
#include "ofMain.h"
#include <memory>

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    shared_ptr<State> currentState;
    shared_ptr<TitleScreenState> titleScreenState;
    shared_ptr<GameState> gameState;
    shared_ptr<GameOverState> gameOverState;
    shared_ptr<Handler> handler;
};
