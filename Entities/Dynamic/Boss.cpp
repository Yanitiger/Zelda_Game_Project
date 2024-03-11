/* -------------------------------------------- Phase 2 -> New Enemy -----------------------------------------------------------*/
#include "Boss.h"

void Boss::update(){
    
    counter++;

    // It is time to stop moving
    if (movingDir[UP] || movingDir[DOWN] || movingDir[LEFT] || movingDir[RIGHT]){
        if (counter == MOVEMENT_TIME){
            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;
            counter = 0;
        }
    }

    else{
        // Time to move in a random direction
        if (counter == WAITING_TIME){
            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;
            movingDir[direction] = true;
            counter = 0;
        }
    }

    DynamicEntity::update();
}

void Boss::damage(int damage){
    if (dead) return;
    // Play the damage sound if we're about to take damage
    if (invincibilityFrames == 0)
        handler->getSoundEffectManager()->playSoundEffect("enemy_hurt");
        
    DynamicEntity::damage(damage);
}

void Boss::onDeath(){
    handler->getSoundEffectManager()->playSoundEffect("enemy_death");
    isDead = true;
}