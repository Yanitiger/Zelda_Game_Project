#pragma once

#include "StaticEntity.h"
#include <memory>

class Fire : public StaticEntity {
public:
    Fire(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~Fire(){};
    void onCollision(shared_ptr<DynamicEntity> e) { e->damage(2); };
};