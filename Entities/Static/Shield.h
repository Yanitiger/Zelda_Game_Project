/* --------------------------------- Bonus Spec -> Shield Item ----------------------------------------- */
#pragma once

#include "StaticEntity.h"
#include "Item.h"
#include "Link.h"
#include <memory>

class Shield : public Item {
public:

    Shield(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite) {}
    ~Shield(){};

/* If link picked up the shield make him take less damge and change his movement animation */
    void applyEffect(shared_ptr<Link> link) {
        link->setShieldOnUSe(true);
        link->setShield(true);
    }

};