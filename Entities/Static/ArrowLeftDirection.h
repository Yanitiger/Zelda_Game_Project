#pragma once

#include "ArrowDirection.h"
#include <memory>

class ArrowLeftDirection : public ArrowDirection {
public:
    ArrowLeftDirection(int x, int y, shared_ptr<Handler> handler) : ArrowDirection(x, y, handler) {}
    ~ArrowLeftDirection(){};

    void onCollision(shared_ptr<DynamicEntity> e) {
        if (this->collidesWith(e)) {
            // e->setX(getX() - 1);
            e->move(LEFT);
            return this->onCollision(e);
        } else {
            return;
       }
    }
};