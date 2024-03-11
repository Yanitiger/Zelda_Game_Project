#include "DynamicEntity.h"

void DynamicEntity::update(){
    this->currentAnimation->update();

    if (this->invincibilityFrames > 0)
        this->invincibilityFrames--;

    if (dead)
        return;

    if (this->movingDir[UP]){
        this->move(UP);
    }
    if (this->movingDir[DOWN]){
        this->move(DOWN);
    }
    if (this->movingDir[LEFT]){
        this->move(LEFT);
    }
    if (this->movingDir[RIGHT]){
        this->move(RIGHT);
    }
}

void DynamicEntity::draw(){
    this->currentSprite = this->currentAnimation->getCurrentFrame();
    Entity::draw();
}

void DynamicEntity::move(Direction d){
    if (dead)
        return;
    switch (d){
        case UP:
            this->setY(this->getY() - this->speed);
            if (this->getY() < Handler::GAME_SCREEN.getTop())
                this->setY(Handler::GAME_SCREEN.getTop());
        /*----------------------------------------- Bonus Spec -----------------------------------------------*/
        // Has link pick up the shield? If he has, set the movement animation to the one with the big shield B)
            if(shield) {
               this->currentAnimation = this->animations->movement2.up; 
            }else this->currentAnimation = this->animations->movement.up;
            break;

        case DOWN:
            this->setY(this->getY() + this->speed);
            if (this->getY() > Handler::GAME_SCREEN.getBottom() - this->getHeight())
                this->setY(Handler::GAME_SCREEN.getBottom() - this->getHeight());
            if(shield) {
               this->currentAnimation = this->animations->movement2.down; 
            }else this->currentAnimation = this->animations->movement.down;
            break;

        case LEFT:
            this->setX(this->getX() - this->speed);
            if (this->getX() < Handler::GAME_SCREEN.getLeft())
                this->setX(Handler::GAME_SCREEN.getLeft());
            if(shield) {
               this->currentAnimation = this->animations->movement2.left; 
            }else this->currentAnimation = this->animations->movement.left;
            break;

        case RIGHT:
            this->setX(this->getX() + this->speed);
            if (this->getX() > Handler::GAME_SCREEN.getRight() - this->getWidth())
                this->setX(Handler::GAME_SCREEN.getRight() - this->getWidth());
            if(shield) {
               this->currentAnimation = this->animations->movement2.right; 
            } else this->currentAnimation = this->animations->movement.right;
            break;
    }
}

void DynamicEntity::damage(int damage)
{
    if (dead) return;
    if (this->invincibilityFrames == 0)
    {
            this->health -= damage;
            this->invincibilityFrames = 30;
            if (this->health <= 0)
            {
                this->health = 0;
                this->dead = true;
                this->onDeath();
            }
    }
}