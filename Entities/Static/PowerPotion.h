/* --------------------------------- Bonus Spec -> Power Item ----------------------------------------- */
#pragma once

#include "StaticEntity.h"
#include "Item.h"
#include "Link.h"
#include <memory>

class PowerPotion : public Item {
public:

    PowerPotion(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite) {}
    ~PowerPotion(){};
    
    void applyEffect(shared_ptr<Link> link) {
        link->setPower(true);
    }

};