#include "GameOverState.h"

void GameOverState::update(){
}

void GameOverState::draw(){
    ofSetColor(255, 255, 255);
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
    heart.draw(ofGetWidth()/4, ofGetHeight() * (0.3 + 0.115 * option), Handler::TILE_WIDTH, Handler::TILE_HEIGHT);
}

void GameOverState::reset(){
    this->musicFileName = "lose.wav";
    option = 0;
    screen = handler->getImageManager()->gameOverScreenWithOptions;
    heart = handler->getImageManager()->heart;
}

void GameOverState::keyPressed(int key){
    if (key == 'w')
        option--;

    if (key == 's')
        option++;

    if (option < 0)
        option = 0;

    if (option > 2)
        option = 2;
        
    if (key == OF_KEY_RETURN || key == ' ') {
        if (option == 1) { // Retry
            this->setFinished(true);
            this->setNextState(TITLE_SCREEN);
        } else if (option == 2) { // Quit
            ofExit(0);
        } else {
            this->setFinished(true);
            this->setNextState(GAME);
        }
    }
}

void GameOverState::keyReleased(int key){

}