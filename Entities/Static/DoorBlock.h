#pragma once

#include "StaticEntity.h"
#include <memory>

enum MapName {
    OVER_WORLD,
    OLD_MANS_CAVE,
    DUNGEON,
    FIRE_DUNGEON
};

class DoorBlock : public StaticEntity {
protected:
    MapName whereTo;

public:
    DoorBlock(int x, int y, shared_ptr<Handler> handler, MapName whereTo) : StaticEntity(x, y, handler) {
        this->whereTo = whereTo;
    }
    ~DoorBlock(){};

    // Doors do nothing. Door collision is handled in the Map and GameState since it's a special case
    void onCollision(shared_ptr<DynamicEntity> e){};

    MapName getWhereTo() { return whereTo; }
};