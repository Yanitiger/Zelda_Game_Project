#include "BoundBlock.h"

void BoundBlock::onCollision(shared_ptr<DynamicEntity> e)
{

    /* Note from Jann:
    *  Esteemed reader. Should you find this code in the future, please know that I am sorry.
    *  Please do not look at this code for too long. It is not good for your health.
    *  It is shy, and WILL break if you look at it for too long.
    */

    // Move the entity back using the Separating Axis Theorem
    // https://www.metanetsoftware.com/technique/tutorialA.html

    // Get the two rectangles
    ofRectangle r1 = e->getBounds();
    ofRectangle r2 = this->getBounds();

    // Get the center of each rectangle
    ofVec2f c1 = ofVec2f(r1.getCenter().x, r1.getCenter().y);
    ofVec2f c2 = ofVec2f(r2.getCenter().x, r2.getCenter().y);

    // Get the half-widths and half-heights of each rectangle
    ofVec2f h1 = ofVec2f(r1.getWidth() / 2, r1.getHeight() / 2);
    ofVec2f h2 = ofVec2f(r2.getWidth() / 2, r2.getHeight() / 2);

    // Get the difference between the centers of the two rectangles
    ofVec2f d = c1 - c2;

    // Get the absolute value of the difference
    d.x = abs(d.x);

    // If the difference in x is less than the sum of the half-widths, then there is a collision
    if (d.x <= h1.x + h2.x){
        // If the difference in y is less than the sum of the half-heights, then there is a collision
        d.y = abs(d.y);
        if (d.y <= h1.y + h2.y){
            // There is a collision
            // Move entity back

            // If the x difference is less than the y difference, then move the entity back in the x direction
            // Otherwise, move the entity back in the y direction
            int xDiff = h1.x + h2.x - d.x;
            int yDiff = h1.y + h2.y - d.y;

            if (xDiff < yDiff){
                // Move entity back in the x direction
                if (c1.x < c2.x)
                    e->setX(e->getX() - xDiff);
                else
                    e->setX(e->getX() + xDiff);
            }
            else{
                // Move entity back in the y direction
                if (c1.y < c2.y)
                    e->setY(e->getY() - yDiff);
                else
                    e->setY(e->getY() + yDiff);
            }
        }
    }
}
