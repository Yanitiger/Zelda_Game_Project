#pragma once

#include "DynamicEntity.h"

class Boss : public DynamicEntity {
    private:
        int counter;
        const int WAITING_TIME = 300;
        const int MOVEMENT_TIME = 30;

    public: 
        Boss(int x, int y, shared_ptr<Handler> handler, shared_ptr<DynamicEntityAnimations> animations) : DynamicEntity(x, y, handler, animations) {
            this->MAX_HEALTH = 1;
            this->health = MAX_HEALTH;
            this->counter = 0;
        };

        Direction direction = DOWN;
        void update();
        void damage(int damage);
        void onDeath();
        void onCollision(shared_ptr<DynamicEntity> entity){entity->damage(20);};

        bool isDead = false;
        bool getBossIsDead() {
            return isDead;
        } 
        void setDirection(Direction dir) {this->direction = dir;}
};