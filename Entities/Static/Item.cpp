#include "Item.h"

void Item::onCollision(shared_ptr<DynamicEntity> e) {
    shared_ptr<Link> link = dynamic_pointer_cast<Link>(e);
    if (link && !isCollected){
        isCollected = true;
        // Set the item's position to be above link
        this->x = link->getX();
        this->y = link->getY() - link->getHeight();

        // Apply the effect of the item
        applyEffect(link);

        // Pick up the item
        link->pickup();

        // Play the sound effect
        handler->getSoundEffectManager()->playSoundEffect("item_get");
    }           
};