#pragma once

#include "BoundBlock.h"
#include "DynamicEntity.h"
#include "ImageManager.h"
#include <memory>

using namespace std;

class Link : public DynamicEntity {

private:
    bool attacking = false;
    bool isPickingUp;
    int dyingTimer;                            // How many frames before we transfer to the Game Over screen
    const int swordOffsets[4] = {0, 11, 7, 3}; // The number of pixels the sword is offset from link for each frame of the attack animation
    ofRectangle swordHitbox;
    ofRectangle staffEffect;
    bool pause = false;

public:
    Link(int x, int y, shared_ptr<Handler> handler, shared_ptr<LinkAnimations> animations) : DynamicEntity(x, y, handler, animations) {
        this->attacking = false;
        this->isPickingUp = false;
        this->dyingTimer = 0;
        this->swordHitbox = ofRectangle(0, 0, 0, 0);
        this->MAX_HEALTH = 20;
        this->health = MAX_HEALTH;
    }
    void update();
    void drawHearts(int hudHeight);
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void move(Direction direction);
    bool isDead() { return dead && dyingTimer == 0; };

    void damage(int damage);
    void onDeath();
    void onCollision(shared_ptr<DynamicEntity> e);

    void pickup(){isPickingUp = true; currentAnimation = getAnimations()->pickup;};
    void unPickup(){isPickingUp = false; currentAnimation = getAnimations()->movement.down;}
    bool getIsPickingUp(){return isPickingUp;};

    int getHealth(){return this->health;}
    ofRectangle getSwordHitbox() { return swordHitbox; }

    shared_ptr<LinkAnimations> getAnimations() { return static_pointer_cast<LinkAnimations>(animations); }

    bool choosenSword = false;
    bool powerActivated = false;
    bool choosenStaff = false;
    bool choosenShield = false;
    bool staffPower = false;
    bool choosenWeapon = false;
    bool isAutoMove = false;
    bool onArrow = false;
    ofImage weaponOnUse;
    ofImage drawThisOne;

    Direction arrowDirection;

    void setStaffOnUse(bool type);
    void setSwordOnUse(bool type);
    void setPower(bool type);
    void setAutoMove(bool type) {this->isAutoMove = type;};
    void setOnArrow(bool type) {this->onArrow = type;};
    bool getAutoMove() {return isAutoMove;};
    bool getOnArrow() {return onArrow;};
    void setShieldOnUSe(bool type);
    void heal(int heal);

    bool getIsAttacking() {return attacking;};
    
    void autoMove(Direction dir);
    void setArrowDirection(Direction dir) {this->arrowDirection = dir;}
};