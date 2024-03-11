#pragma once

#include "ArrowDirection.h"
#include <memory>

class ArrowDownDirection : public ArrowDirection {
public:
    ArrowDownDirection(int x, int y, shared_ptr<Handler> handler) : ArrowDirection(x, y, handler) {}
    ~ArrowDownDirection(){};

    void onCollision(shared_ptr<DynamicEntity> e) {
        if (!this->collidesWith(e)) {
            return;
        } else {
            //e->setY(getY() - 1);
            e->move(DOWN);
            return this->onCollision(e);
        }
    }
};