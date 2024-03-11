#pragma once

#include "StaticEntity.h"
#include "Item.h"
#include "Link.h"
#include <memory>

class Sword : public Item {
public:

    Sword(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite) {}
    ~Sword(){};

    void applyEffect(shared_ptr<Link> link) {
        link->setSwordOnUse(true);
    }

};