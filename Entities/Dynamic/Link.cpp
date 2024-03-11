#include "Link.h"
#include "ImageManager.h"

void Link::update() {
    DynamicEntity::update();

    if (dyingTimer > 0)
        dyingTimer--;

    if (dead)
        return;

    if (this->health <= 2)
        this->handler->getSoundEffectManager()->playSoundEffect("link_low_health"); 
//-------------------------------------------------------
    if (attacking)
    {
        if (currentAnimation->hasEnded())
        {
            // Reset the weaponOnUse hitbox
            swordHitbox = ofRectangle(0, 0, 0, 0);
            attacking = false;
            currentAnimation->reset();
            if(choosenShield == true) {
                if (currentAnimation == getAnimations()->attacking.up)
                    this->currentAnimation = getAnimations()->movement2.up;
                else if (currentAnimation == getAnimations()->attacking.down)
                    this->currentAnimation = getAnimations()->movement2.down;
                else if (currentAnimation == getAnimations()->attacking.left)
                    this->currentAnimation = getAnimations()->movement2.left;
                else if (currentAnimation == getAnimations()->attacking.right)
                    this->currentAnimation = getAnimations()->movement2.right;
            } else {
                if (currentAnimation == getAnimations()->attacking.up)
                    this->currentAnimation = getAnimations()->movement.up;
                else if (currentAnimation == getAnimations()->attacking.down)
                    this->currentAnimation = getAnimations()->movement.down;
                else if (currentAnimation == getAnimations()->attacking.left)
                    this->currentAnimation = getAnimations()->movement.left;
                else if (currentAnimation == getAnimations()->attacking.right)
                    this->currentAnimation = getAnimations()->movement.right;
            }
            
        }
    }

    weaponOnUse = drawThisOne;

}

void Link::draw() {
//------------------------------------------------------------
    if (attacking) {
        // The goal is to draw the weaponOnUse on top of link, offset by the swordOffsets array
        int offset = swordOffsets[currentAnimation->getIndex()];
        
        // Because the weaponOnUse is not centered in the 16x16 square, we have to
        // offset the weaponOnUse by a few pixels to make it look right
        
        // The weaponOnUse is offset by 2 pixels to the left when facing up, 1 pixel to the right when facing down
        // 2 pixels down when facing left, and 1 pixel down when facing right
        int xOffset = 1;
        int yOffset = 1;

        // Determine the direction the weaponOnUse should be drawn in
        Direction swordDirection = UP;

        if (currentAnimation == getAnimations()->attacking.up) {
            swordDirection = UP;
            yOffset = -offset;
            xOffset = -2; // Funny special case
        } else if (currentAnimation == getAnimations()->attacking.down) {
            swordDirection = DOWN;
            yOffset = offset;
        } else if (currentAnimation == getAnimations()->attacking.left) {
            swordDirection = LEFT;
            xOffset = -offset;
            yOffset = 2; // Funny special case
        } else if (currentAnimation == getAnimations()->attacking.right) {
            swordDirection = RIGHT;
            xOffset = offset;
        }

        // Get the weaponOnUse image
        // ofImage weaponOnUse = handler->getImageManager()->magicStaff;


        ofImage effect = handler->getImageManager()->staffEffect;

        // Rotate the weaponOnUse if necessary.
        // By default, the weaponOnUse is facing up
        if (swordDirection == DOWN) {
            weaponOnUse.rotate90(2);
        }
        else if (swordDirection == LEFT) {
            weaponOnUse.rotate90(-1);
        }
        else if (swordDirection == RIGHT) {
            weaponOnUse.rotate90(-3);
        }

        // Calculate the weaponOnUse hitbox
        swordHitbox = ofRectangle(x + xOffset * Handler::PIXEL_SCALE, y + yOffset * Handler::PIXEL_SCALE, width, height);
        staffEffect = ofRectangle(x + xOffset * (Handler::PIXEL_SCALE) * 3, y + yOffset * (Handler::PIXEL_SCALE) * 2, width, height);
        // Draw the weaponOnUse
        weaponOnUse.draw(swordHitbox);

        // if(staffPower) {
        //    effect.draw(staffEffect); 
        // }
    }

    DynamicEntity::draw();

    if (Handler::DEBUG){
        ofSetColor(255,0,0);
        ofSetLineWidth(Handler::PIXEL_SCALE);
        ofNoFill();
        ofDrawRectangle(swordHitbox);
        ofFill();
        ofSetColor(255, 255, 255);
    }
}

void Link::setSwordOnUse(bool type) {
    choosenSword = type;
}

void Link::setStaffOnUse(bool type) {
    choosenStaff = type;
}

void Link::setShieldOnUSe(bool type) {
    choosenShield = type;
}

void Link::setPower(bool type) {
    powerActivated = type;
}


void Link::move(Direction direction) {
    // Link can only move if he is not attacking
    if (!attacking)
        DynamicEntity::move(direction);
}

void Link::heal(int heal) {
    this->health = getHealth() + heal;
}

void Link::damage(int damage) {
    if (dead)
        return;

    // Play the damage sound if we're about to take damage
    if (invincibilityFrames == 0)
        handler->getSoundEffectManager()->playSoundEffect("link_hurt");

/* If link has the shield equip the halved all the damage he receives, thats nice :D*/
    if(choosenShield) {
        damage = damage/2;
        DynamicEntity::damage(damage);
        
    } else {
       DynamicEntity::damage(damage); 
    }
        
    // Should lower health and give invincibility frames
    // DynamicEntity::damage(damage);
}

void Link::onDeath() {
    // Play the death sound
    handler->getSoundEffectManager()->playSoundEffect("link_death");
    handler->getMusicManager()->stopMusic();
    currentAnimation = getAnimations()->death;
    dyingTimer = 150;
}
void Link::onCollision(shared_ptr<DynamicEntity> e) {
    if (dead)
        return;
    
    if(powerActivated) {
        e->damage(2);
    } else if(choosenStaff) {
        e->damage(20);
    } 
    else e->damage(1);
}

void Link::drawHearts(int hudHeight) {

    // Handles everything regarding hearts
    ofImage fullHeart = handler->getImageManager()->fullHeart;
    ofImage halfHeart = handler->getImageManager()->halfHeart;
    ofImage emptyHeart = handler->getImageManager()->emptyHeart;
    int acc = 0;

    // Draws the Full Heart
    for (int i = 0; i < health / 2; i++)
    {
        if (i <= 7 || health <= 7)
        {
            fullHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * i), hudHeight - ofGetHeight()/8, Handler::TILE_WIDTH, Handler::TILE_HEIGHT); // Row 1
        }

        if (i >= 8 && i <= 16)
        {
            fullHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * (i - 8)), hudHeight - ofGetHeight()/12, Handler::TILE_WIDTH, Handler::TILE_HEIGHT); // Row 2
        }
        acc = i + 1;
    }

    // Draws the Half Heart
    if (health % 2 == 1)
    {
        if (health <= 16)
        {
            halfHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * acc), hudHeight - ofGetHeight()/8, Handler::TILE_WIDTH, Handler::TILE_HEIGHT);
        }

        else if (health <= 32)
        {
            halfHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * (acc - 8)), hudHeight - ofGetHeight()/12, Handler::TILE_WIDTH, Handler::TILE_HEIGHT);
        }
    }

    // Draws the Remainder Hearts
    //  (health + 1 )/2 gives us the starting position, we loop until the maxHealth/2 which is the max position
    for (int i = (health + 1) / 2; i < MAX_HEALTH / 2; i++)
    {
        if (i <= 7)
        {
            emptyHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * i),hudHeight - ofGetHeight()/8, Handler::TILE_WIDTH, Handler::TILE_HEIGHT);
        }

        if (i >= 8 && i <= 16)
        {
            emptyHeart.draw((4 * ofGetWidth()) / 6 + (ofGetWidth()/32 * (i - 8)), hudHeight - ofGetHeight()/12, Handler::TILE_WIDTH, Handler::TILE_HEIGHT);
        }
    }
}

void Link::keyPressed(int key) {
    if (!pause){
        if (this->getIsPickingUp() || dead) return;
        

        if (key == 'w' || key == OF_KEY_UP)
            this->movingDir[UP] = true;
        
        else if (key == 's' || key == OF_KEY_DOWN)
            this->movingDir[DOWN] = true;

        else if (key == 'a' || key == OF_KEY_LEFT)
            this->movingDir[LEFT] = true;

        else if (key == 'd' || key == OF_KEY_RIGHT)
            this->movingDir[RIGHT] = true;
        
 /* If C has been pressed and he has collected the staff, then enable him to attack with the staff */
        if (key == 'c' && (choosenStaff)) {
            drawThisOne = handler->getImageManager()->magicStaff;
            if (attacking || dead)
                return;
        //--------------------------------------------------------------------------------
                
            this->attacking = true;
            /* If links has collected the shield then change his movement */
            if(choosenShield) {
                if (currentAnimation == getAnimations()->movement2.up)
                    this->currentAnimation = getAnimations()->attacking.up;
                else if (currentAnimation == getAnimations()->movement2.down)
                    this->currentAnimation = getAnimations()->attacking.down;
                else if (currentAnimation == getAnimations()->movement2.left)
                    this->currentAnimation = getAnimations()->attacking.left;
                else if (currentAnimation == getAnimations()->movement2.right)
                    this->currentAnimation = getAnimations()->attacking.right;
            } else {
                if (currentAnimation == getAnimations()->movement.up)
                this->currentAnimation = getAnimations()->attacking.up;
            else if (currentAnimation == getAnimations()->movement.down)
                this->currentAnimation = getAnimations()->attacking.down;
            else if (currentAnimation == getAnimations()->movement.left)
                this->currentAnimation = getAnimations()->attacking.left;
            else if (currentAnimation == getAnimations()->movement.right)
                this->currentAnimation = getAnimations()->attacking.right;
            }
            
            
            

            // Play the weaponOnUse sound
            handler->getSoundEffectManager()->playSoundEffect("link_sword_attack");
        }

/* If B/space has been pressed and link has collected the sword, then enable him to attack with the sword */
        else if ((key == ' ' || key == 'b') && (choosenSword)) {
/* If the power has been activated then draw the red Sword */
            if(powerActivated) {
                drawThisOne = handler->getImageManager()->redSword;
            } else drawThisOne = handler->getImageManager()->basicSword;
            
            if (attacking || dead)
                return;
        //--------------------------------------------------------------------------------
                
            this->attacking = true;
            /* If links has collected the shield then change his movement */
            if(choosenShield) {
                if (currentAnimation == getAnimations()->movement2.up)
                    this->currentAnimation = getAnimations()->attacking.up;
                else if (currentAnimation == getAnimations()->movement2.down)
                    this->currentAnimation = getAnimations()->attacking.down;
                else if (currentAnimation == getAnimations()->movement2.left)
                    this->currentAnimation = getAnimations()->attacking.left;
                else if (currentAnimation == getAnimations()->movement2.right)
                    this->currentAnimation = getAnimations()->attacking.right;
            } else {
                if (currentAnimation == getAnimations()->movement.up)
                this->currentAnimation = getAnimations()->attacking.up;
            else if (currentAnimation == getAnimations()->movement.down)
                this->currentAnimation = getAnimations()->attacking.down;
            else if (currentAnimation == getAnimations()->movement.left)
                this->currentAnimation = getAnimations()->attacking.left;
            else if (currentAnimation == getAnimations()->movement.right)
                this->currentAnimation = getAnimations()->attacking.right;
            }

            // Play the weaponOnUse sound
            handler->getSoundEffectManager()->playSoundEffect("link_sword_attack");
        }
    }
}

void Link::keyReleased(int key) {
    if (key == 'w')
        this->movingDir[UP] = false;

    else if (key == 's')
        this->movingDir[DOWN] = false;

    else if (key == 'a')
        this->movingDir[LEFT] = false;

    else if (key == 'd')
        this->movingDir[RIGHT] = false;
}