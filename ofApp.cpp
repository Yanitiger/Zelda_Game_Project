#include "ofApp.h"
#include <memory>

using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
    handler = make_shared<Handler>(make_unique<SoundEffectManager>(), make_unique<ImageManager>(), make_unique<MusicManager>());

    titleScreenState = make_shared<TitleScreenState>(handler);
    gameState = make_shared<GameState>(handler);
    gameOverState = make_shared<GameOverState>(handler);

    currentState = titleScreenState;

    if (currentState->getMusicFileName() != "")
        handler->getMusicManager()->playMusic(currentState->getMusicFileName());
}

//--------------------------------------------------------------
void ofApp::update() {
    handler->getMusicManager()->update();
    handler->getSoundEffectManager()->update();

    if (currentState != nullptr) {
        if (currentState->isFinished()) {
            handler->getMusicManager()->stopMusic();

            StateName nextState = currentState->getNextState();

            // Reset the finished and next state variables
            currentState->setFinished(false);
            currentState->setNextState(UNKNOWN);
            switch (nextState) {
            case TITLE_SCREEN:
                currentState = titleScreenState;
                break;
            case GAME:
                if (currentState == titleScreenState || currentState == gameOverState)
                    gameState->reset();
                currentState = gameState;
                break;
            case GAME_OVER:
                gameOverState->reset();
                currentState = gameOverState;
                break;
            default:
                // Assume an error occurred or the game is finished
                ofExit();
                break;
            }

            // Play the music for the new state
            if (currentState->getMusicFileName() != "")
                handler->getMusicManager()->playMusic(currentState->getMusicFileName());

        }
        currentState->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (currentState != nullptr)
        currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // We do not care about upper or lower case
    // Convert to lower case
    key = tolower(key);
    if (currentState != nullptr) {
        // Reset the current state
        if (key == 'r')
            currentState->reset();

        // Toggle pause
        else if (key == 'm') {
            if (handler->getMusicManager()->isMuted())
                handler->getMusicManager()->unmute();
            else
                handler->getMusicManager()->mute();

            handler->getSoundEffectManager()->setMuted(handler->getMusicManager()->isMuted());
        }

        // Toggle debug mode
        else if (key == '1')
            Handler::DEBUG = !Handler::DEBUG;

        else
            currentState->keyPressed(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    key = tolower(key);
    if (currentState != nullptr)
        currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    if (currentState != nullptr)
        currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

//--------------------------------------------------------------