#pragma once

#include "ArrowDirection.h"
#include <memory>

class ArrowUpDirection : public ArrowDirection {
public:
    ArrowUpDirection(int x, int y, shared_ptr<Handler> handler) : ArrowDirection(x, y, handler) {}
    ~ArrowUpDirection(){};

    void onCollision(shared_ptr<DynamicEntity> e) {
        if (!this->collidesWith(e)) {
            return;
        } else {
            // e->setY(getY() + 1);
            e->move(UP);
            return this->onCollision(e);
        }
    }
};