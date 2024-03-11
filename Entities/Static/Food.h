/* --------------------------------- Bonus Spec -> Healing Item ----------------------------------------- */
#pragma once

#include "StaticEntity.h"
#include "Item.h"
#include "Link.h"
#include <memory>

class Food : public Item {
public:

    Food(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite) {}
    ~Food(){};
    
/* Is link in need of health??????????? :O, then give hime 2 lifes. Thats better >.<*/
    void applyEffect(shared_ptr<Link> link) {
        link->heal(4);
    }

};