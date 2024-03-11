#pragma once
#include "Animation.h"
#include "Entity.h"
#include <memory>

using namespace std;

class DynamicEntity : public Entity {
protected:
    // Whether the entity is moving UP, DOWN, LEFT, or RIGHT
    bool movingDir[4] = {false, false, false, false};
    int health;              // Number of Hearts = health/2
    int MAX_HEALTH;
    int speed;               // How many pixels the entity can move per frame
    int invincibilityFrames; // Number of frames the entity is invincible for after taking damage
    bool dead;               // Whether the entity is dead or not. Dead entities are "hidden" from the game

    shared_ptr<DynamicEntityAnimations> animations;
    shared_ptr<Animation> currentAnimation;

public:
    DynamicEntity(int x, int y, shared_ptr<Handler> handler, shared_ptr<DynamicEntityAnimations> animations) : Entity(x, y, handler) {
        this->animations = animations;
        this->currentAnimation = animations->movement.down;
        this->speed = Handler::PIXEL_SCALE; // Move 1/16th of a tile per frame
        this->invincibilityFrames = 0;
        this->dead = false;
    }

    virtual void update();
    virtual void draw();
    virtual void move(Direction direction);
    virtual bool isDead() { return dead; };
    virtual void revive() { dead = false; this->health = MAX_HEALTH;};
    virtual void damage(int damage);
    virtual void onDeath() = 0;
    virtual void onCollision(shared_ptr<DynamicEntity> entity) = 0;

/*------------------------------ Shield Bonus Spec ----------------------------------*/
// We added this in order to change links movement animation when he picks the shield
    bool shield = false;
    virtual void setShield (bool type) {
        shield = type;
    }
};