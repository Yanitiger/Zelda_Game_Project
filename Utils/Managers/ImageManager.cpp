#include "ImageManager.h"
#include <memory>

ImageManager::ImageManager() {

    ofImage entitySpriteSheet = ofImage("images/SpriteSheets/entitySprites_transparent.png");
    entitySprites = loadSpritesFromSheet(entitySpriteSheet, PIXELS_PER_TILE, PIXELS_PER_TILE, 1);

    ofImage mapSpriteSheet = ofImage("images/SpriteSheets/mapSprites.png");
    mapSprites = loadSpritesFromSheet(mapSpriteSheet, PIXELS_PER_TILE, PIXELS_PER_TILE, 1);

    // ofImage dungeonSpritesSheet = ofImage("images/SpriteSheets/dungeonSprites.png");
    // dungeonTiles = loadSpritesFromSheet(dungeonSpritesSheet, PIXELS_PER_TILE, PIXELS_PER_TILE);

    overWorldPixelMap = ofImage("images/Maps/overWorldPixelMap.png");
    oldMansCavePixelMap = ofImage("images/Maps/oldMansCavePixelMap.png");
    dungeonPixelMap = ofImage("images/Maps/dungeonPixelMap2.png");
    secondDungeonPixelMap = ofImage("images/Maps/dungeonPixelMap1.png");

/* These are the location of all the sprite we use from the entitySpriteSheet */
    basicSword = entitySprites[74];
    redSword = entitySprites[76];
    potion = entitySprites[135];
    magicStaff = entitySprites[78];
    staffEffect = entitySprites[98];
    foodHeal = entitySprites[103];
    shield = entitySprites[120];
    fullHeart = entitySprites[126];
    halfHeart = entitySprites[127];
    emptyHeart = entitySprites[128];

    createLinkAnimations();
    createTitleScreenAnimation();

    gameOverScreen = ofImage("images/GameOverScreen/GameOver_1.png");
    gameOverScreenWithOptions = ofImage("images/GameOverScreen/GameOver_2.png");
    heart = getSpriteFromEntitySheetAt(0, 7);
    HUD = ofImage("images//HUD/HUD.png");
}

// Returns an animation from a list of indices
template <typename... Indices>
shared_ptr<Animation> ImageManager::getAnimationFromIndices(Indices... indices) {
    vector<ofImage> frames{entitySprites[indices]...};
    return make_shared<Animation>(10, frames);
}

void ImageManager::createLinkAnimations() {
    // Movement
    DirectionalAnimations movement;
    movement.down = getAnimationFromIndices(0, 1);
    movement.right = getAnimationFromIndices(2, 3);
    movement.left = getAnimationFromIndices(4, 5);
    movement.up = getAnimationFromIndices(6, 7);

/* Why is there another tipe of movement 0.0, these movement are the ones link carrys the big Shield */
    DirectionalAnimations movement2;
    movement2.down = getAnimationFromIndices(10, 11);
    movement2.right = getAnimationFromIndices(12, 13);
    movement2.left = getAnimationFromIndices(14, 15);
    movement2.up = getAnimationFromIndices(6, 7);

    // Attacking
    DirectionalAnimations attacking;
    attacking.down = getAnimationFromIndices(18, 19, 20, 21);
    attacking.right = getAnimationFromIndices(22, 23);
    attacking.left = getAnimationFromIndices(26, 27);
    attacking.up = getAnimationFromIndices(30, 31, 32, 33);

    

    linkAnimations = make_shared<LinkAnimations>();

    // Misc
    linkAnimations->damage = getAnimationFromIndices(36, 37, 38, 39, 40, 41);
    linkAnimations->death = getAnimationFromIndices(0, 2, 6, 4); // Down, Right, Up, Left
    linkAnimations->pickup = getAnimationFromIndices(9,10);

    // Assign to LinkAnimations
    linkAnimations->attacking = attacking;
    linkAnimations->movement = movement;
    linkAnimations->movement2 = movement2;
    

    // Remove loops from attacking animations
    linkAnimations->attacking.down->setLoop(false);
    linkAnimations->attacking.right->setLoop(false);
    linkAnimations->attacking.left->setLoop(false);
    linkAnimations->attacking.up->setLoop(false);

    // Speed up the attacking animations
    linkAnimations->attacking.down->setSpeed(5);
    linkAnimations->attacking.right->setSpeed(5);
    linkAnimations->attacking.left->setSpeed(5);
    linkAnimations->attacking.up->setSpeed(5);
    

}

shared_ptr<DynamicEntityAnimations> ImageManager::getTektikeAnimations(){
    DirectionalAnimations movement;
    
    // Tektike's movement animation is the same for all directions
    movement.down = getAnimationFromIndices(123,124);
    movement.right = movement.down;
    movement.left = movement.down;
    movement.up = movement.down;

    tektikeAnimations = make_shared<DynamicEntityAnimations>();

    tektikeAnimations->movement = movement;

    // No attacking animation for Tektike
    tektikeAnimations->attacking = movement;

    tektikeAnimations->damage = getAnimationFromIndices(87, 88);
    tektikeAnimations->explode = getAnimationFromIndices(100,101,102);

    return tektikeAnimations;

}

shared_ptr<DynamicEntityAnimations> ImageManager::getBossAnimations(){
    DirectionalAnimations movement;
    
    // Tektike's movement animation is the same for all directions
    movement.down = getAnimationFromIndices(68,69);
    movement.right = getAnimationFromIndices(66,67);
    movement.left = getAnimationFromIndices(70,71);
    movement.up = getAnimationFromIndices(17,35);

    tektikeAnimations = make_shared<DynamicEntityAnimations>();

    tektikeAnimations->movement = movement;

    // No attacking animation for Tektike
    tektikeAnimations->attacking = movement;

    tektikeAnimations->damage = getAnimationFromIndices(87, 88);

    return tektikeAnimations;

}

/* Dungeon Tektike are the shiny version of the overWorld tektike. Really rare, I should catch one */
shared_ptr<DynamicEntityAnimations> ImageManager::getDungeonTektikeAnimations(){
    DirectionalAnimations movement;
    
    // Tektike's movement animation is the same for all directions
    movement.down = getAnimationFromIndices(105,106);
    movement.right = movement.down;
    movement.left = movement.down;
    movement.up = movement.down;

    tektikeAnimations = make_shared<DynamicEntityAnimations>();

    tektikeAnimations->movement = movement;

    // No attacking animation for Tektike
    tektikeAnimations->attacking = movement;

    tektikeAnimations->damage = getAnimationFromIndices(87, 88);
    tektikeAnimations->explode = getAnimationFromIndices(100,101,102);

    return tektikeAnimations;

}

void ImageManager::createTitleScreenAnimation() {
    // Read from data/images/TitleScreenFrames
    vector<ofImage> frames;
    for (int i = 0; i < 16; i++) {
        ofImage frame = ofImage("images/TitleScreenFrames/frame" + to_string(i) + ".png");
        frames.push_back(frame);
    }
    titleScreenAnimation = make_shared<Animation>(5, frames);
}

vector<ofImage> ImageManager::loadSpritesFromSheet(ofImage sheet, int spriteWidth, int spriteHeight, int borderSize) {
    vector<ofImage> sprites;
    for (int y = borderSize; y + spriteHeight < sheet.getHeight(); y += spriteHeight + borderSize) {
        for (int x = borderSize; x + spriteWidth < sheet.getWidth(); x += spriteWidth + borderSize) {
            ofImage sprite;
            sprite.cropFrom(sheet, x, y, spriteWidth, spriteHeight);
            sprites.push_back(sprite);
        }
    }
    return sprites;
}

ofImage ImageManager::getSpriteFromEntitySheetAt(int column, int row) {
    // 18 tiles per row (y)
    // index = 18y + x
    return entitySprites[(row * 18) + column];
}
ofImage ImageManager::getSpriteFromMapSheetAt(int column, int row) {
    // 32 tiles per row (y)
    // index = 32y + x
    return mapSprites[(row * 32) + column];
}