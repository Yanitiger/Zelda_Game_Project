#include "TitleScreenState.h"

void TitleScreenState::update(){
    this->titleScreenAnimation->update();
}

void TitleScreenState::draw(){
    this->titleScreenAnimation->draw(0, 0, ofGetWidth(), ofGetHeight());
}

void TitleScreenState::reset(){
    this->musicFileName = "intro.wav";
    this->titleScreenAnimation = this->handler->getImageManager()->titleScreenAnimation;
    this->titleScreenAnimation->reset();
}

void TitleScreenState::keyPressed(int key){
    if (key == ' ' || key == OF_KEY_RETURN)
    {
        this->setFinished(true);
        this->setNextState(GAME);
    }
}

void TitleScreenState::keyReleased(int key){

}