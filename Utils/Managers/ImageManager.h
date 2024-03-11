#pragma once

#include "Animation.h"
#include "ofMain.h"
#include <memory>
#include <vector>

// Animations that change based on direction
class DirectionalAnimations {
public:
    shared_ptr<Animation> up;
    shared_ptr<Animation> down;
    shared_ptr<Animation> left;
    shared_ptr<Animation> right;

    shared_ptr<Animation> up2;
    shared_ptr<Animation> down2;
    shared_ptr<Animation> left2;
    shared_ptr<Animation> right2;
};

// Animations used by all DynamicEntities
class DynamicEntityAnimations {
public:
    DirectionalAnimations movement;
    DirectionalAnimations movement2;
    DirectionalAnimations attacking;
    shared_ptr<Animation> damage;
    shared_ptr<Animation> explode;
};

// Animations used by Link
class LinkAnimations : public DynamicEntityAnimations {
public:

    
    shared_ptr<Animation> death;
    shared_ptr<Animation> pickup;
};

/**
 * ImageManager is a class that contains all of the images used in the game.
 */
class ImageManager {
private:
    vector<ofImage> entitySprites;
    vector<ofImage> mapSprites;

    template <typename... Indices>
    shared_ptr<Animation> getAnimationFromIndices(Indices... indices);
    void createLinkAnimations();
    void createEnemyAnimations();
    void createTitleScreenAnimation();

    // Loads all sprites from a sprite sheet into a vector of images
    vector<ofImage> loadSpritesFromSheet(ofImage sheet, int spriteWidth, int spriteHeight, int borderSize = 0);

public:
    ImageManager();

    // TODO: Add your image declarations here
    ofImage gameOverScreen;
    ofImage gameOverScreenWithOptions;
    ofImage basicSword;
    ofImage redSword;
    ofImage magicStaff;
    ofImage staffEffect;
    ofImage foodHeal;
    ofImage potion;
    ofImage shield;
    ofImage overWorldPixelMap;
    ofImage oldMansCavePixelMap;
    ofImage dungeonPixelMap;
    ofImage secondDungeonPixelMap;
    ofImage heart;
    ofImage HUD;
    ofImage fullHeart;
    ofImage halfHeart;
    ofImage emptyHeart;

    // TODO: Add your animation declarations here
    shared_ptr<LinkAnimations> linkAnimations;
    shared_ptr<DynamicEntityAnimations> tektikeAnimations;
    shared_ptr<Animation> titleScreenAnimation;

    ofImage getSpriteFromEntitySheetAt(int column, int row);
    ofImage getSpriteFromMapSheetAt(int column, int row);
    shared_ptr<DynamicEntityAnimations> getTektikeAnimations();
    shared_ptr<DynamicEntityAnimations> getDungeonTektikeAnimations();
    shared_ptr<DynamicEntityAnimations> getBossAnimations();
    const int PIXELS_PER_TILE = 16;
};