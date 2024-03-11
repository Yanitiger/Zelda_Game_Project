/* --------------------------------- Bonus Spec -> Extra Weapon Item ----------------------------------------- */
#pragma once

#include "StaticEntity.h"
#include "Item.h"
#include "Link.h"
#include <memory>

class MagicStaff : public Item {
public:

    MagicStaff(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite) {}
    ~MagicStaff(){};

    void applyEffect(shared_ptr<Link> link) {
        link->setStaffOnUse(true);
    }

};