#pragma once

#include "ArrowDirection.h"
#include <memory>

class ArrowRightDirection : public ArrowDirection {
public:
    ArrowRightDirection(int x, int y, shared_ptr<Handler> handler) : ArrowDirection(x, y, handler) {}
    ~ArrowRightDirection(){};

    void onCollision(shared_ptr<DynamicEntity> e) {
        if (!this->collidesWith(e)) {
            return;
        } else {
            // e->setY(getX() + 1);
            e->move(RIGHT);
            return this->onCollision(e);
        }
    }
};