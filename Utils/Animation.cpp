#include "Animation.h"

void Animation::update(){
    // if animation has ended, do nothing
    if (end) return;

    timer++;
    if(timer > speed){
        index++;
        if(index == frames.size()){
            if (loop)
                this->reset();
            

            else{
                end = true;
                index = frames.size() - 1; // last frame
            }
        }
        timer = 0;
    }
}

void Animation::draw(int x, int y, int w, int h){
    this->getCurrentFrame().draw(x, y, w, h);
}

ofImage Animation::getCurrentFrame(){
    return frames[index];
}

void Animation::reset(){
    this->timer = 0;
    this->index = 0;
    this->end = false;
}