#pragma once

#include "StaticEntity.h"
#include <memory>

class ArrowDirection : public StaticEntity {
public:
    ArrowDirection(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~ArrowDirection(){};

    virtual void onCollision(shared_ptr<DynamicEntity> e) {};
};