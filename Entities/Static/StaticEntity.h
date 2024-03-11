#pragma once

#include "DynamicEntity.h" // Included to complete the forward declaration
#include "Entity.h"        // Includes incomplete definition of DynamicEntity
#include <memory>

/**
 * Static entities are entities that do not move and are interacted with by DynamicEntities
 *
 * By default, these entities are not drawn, but can be drawn if they have a sprite/animation associated with them.
 */
class StaticEntity : public Entity {
protected:
    shared_ptr<Handler> handler;


public:
    StaticEntity(int x, int y, shared_ptr<Handler> handler) : Entity(x, y, handler) {
        this->x = x;
        this->y = y;
        this->handler = handler;
    }

    virtual void update(){}; // Not all static entities need to update
    virtual void draw() {
        // Not all static entities have sprites
        if (currentSprite.isAllocated())
            Entity::draw();
    };

    virtual void onCollision(shared_ptr<DynamicEntity>) = 0;
};