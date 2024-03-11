#pragma once
#include "Handler.h"
#include "ofMain.h"
#include <memory>

using namespace std;

// Forward declaration
// This allows us to use the DynamicEntity class in the Entity class
class DynamicEntity;

class Entity {

protected:
    int x;
    int y;
    int width;
    int height;
    ofImage currentSprite;
    shared_ptr<Handler> handler;

public:
    Entity(int x, int y, shared_ptr<Handler> handler) {
        this->x = x;
        this->y = y;

        // By default, the width and height of an entity is the size of a tile
        this->width = Handler::TILE_WIDTH;
        this->height = Handler::TILE_HEIGHT;

        this->handler = handler;
    }
    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

    ofRectangle getBounds() { return ofRectangle(x, y, width, height); }
    bool collidesWith(shared_ptr<Entity> e) { return this->getBounds().intersects(e->getBounds()); }

    virtual void draw() { 
        currentSprite.draw(x, y, width, height); 
        if (Handler::DEBUG){
            ofNoFill();
            ofSetLineWidth(Handler::PIXEL_SCALE);
            ofSetColor(ofColor::green);
            ofDrawRectangle(getBounds());
            ofFill();
            ofSetColor(255, 255, 255);
        }
    }
    
    virtual void update() = 0;
    virtual void onCollision(shared_ptr<DynamicEntity>) = 0;
};