#pragma once

#include "StaticEntity.h"
#include <memory>

class BoundBlock : public StaticEntity {

public:
    BoundBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~BoundBlock(){};
    virtual void onCollision(shared_ptr<DynamicEntity> e);
};