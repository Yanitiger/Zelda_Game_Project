#pragma once

#include "DynamicEntity.h"

class Tektike : public DynamicEntity {
    private:
        int counter;
        const int WAITING_TIME = 60;
        const int MOVEMENT_TIME = 30;

    public: 
        Tektike(int x, int y, shared_ptr<Handler> handler, shared_ptr<DynamicEntityAnimations> animations) : DynamicEntity(x, y, handler, animations) {
            this->MAX_HEALTH = 4;
            this->health = MAX_HEALTH;
            this->counter = 0;
        };

        void update();
        void damage(int damage);
        void onDeath();
        void onCollision(shared_ptr<DynamicEntity> entity){entity->damage(2);};
        shared_ptr<DynamicEntityAnimations> getAnimations() { return static_pointer_cast<DynamicEntityAnimations>(animations); }
};