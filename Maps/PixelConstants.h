#include "ofMain.h"

struct TilePixelColors{
    // Walls
    const ofColor CENTRAL_MOUNTAIN_WALL = ofColor(1, 57, 0);
    const ofColor UPPER_MOUNTAIN_WALL = ofColor(44, 132, 42);
    const ofColor LOWER_RIGHT_MOUNTAIN_CORNER = ofColor(71, 108, 70);
    const ofColor LOWER_LEFT_MOUNTAIN_CORNER = ofColor(157, 226, 155);
    const ofColor UPPER_RIGHT_MOUNTAIN_CORNER = ofColor(114, 176, 113);
    const ofColor UPPER_LEFT_MOUNTAIN_CORNER = ofColor(77, 198, 75);
    
    const ofColor CENTRAL_BROWN_WALL = ofColor(57, 33, 0);
    const ofColor UPPER_BROWN_WALL = ofColor(83, 55, 17);
    const ofColor LOWER_RIGHT_BROWN_CORNER = ofColor(195, 131, 43);
    const ofColor LOWER_LEFT_BROWN_CORNER = ofColor(203, 178, 144);
    const ofColor UPPER_RIGHT_BROWN_CORNER = ofColor(155, 130, 96);
    const ofColor UPPER_LEFT_BROWN_CORNER = ofColor(98, 71, 34);
    const ofColor CAVE_WALL = ofColor(75, 35, 0);
    const ofColor CAVE_UPPER_WALL = ofColor(98, 45, 1);

    // Dungeon Walls
    const ofColor DUNGEON_WALL = ofColor(120,98,117);
    const ofColor DUNGEON_WATER = ofColor(46, 40, 204);
    const ofColor DUNGEON_FALLING_WATER = ofColor(212,118,208);
    const ofColor DUNGEON_DRAGON = ofColor(120,67,118);
    const ofColor DUNGEON_FISH = ofColor(150,84,148);
    const ofColor DUNGEON_ENTRANCE_LEFT = ofColor(171,68,169);
    const ofColor DUNGEON_ENTRANCE_LEFT_UP = ofColor(172,68,169);
    const ofColor DUNGEON_ENTRANCE_RIGHT = ofColor(171,68,170);
    const ofColor DUNGEON_ENTRANCE_RIGHT_UP = ofColor(172,68,170);
    const ofColor DUNGEON_HALF_LEFT_FLOOR = ofColor(207,82,204);
    const ofColor DUNGEON_HALF_RIGHT_FLOOR = ofColor(207,82,205);
    const ofColor DUNGEON_UP_ARROW = ofColor(136, 0, 25);
    const ofColor DUNGEON_DOWN_ARROW = ofColor(136, 0, 30);
    const ofColor DUNGEON_LEFT_ARROW = ofColor(136, 0, 21);
    const ofColor DUNGEON_RIGHT_ARROW = ofColor(136,0 , 35);
    

    

    // Decorations (also walls)
    const ofColor GREEN_TREES = ofColor(2, 131, 0);
    const ofColor CENTRAL_WATER = ofColor(24, 37, 214);
    const ofColor WATER_LOWER_LEFT_CORNER = ofColor(71, 111, 250);
    const ofColor GREEN_SNAIL_BUSH_THINGS = ofColor(124, 255, 121);
    const ofColor BROWN_SNAIL_ROCK_THING = ofColor(178, 108, 11);
    const ofColor BLACK_ENTRANCE = ofColor(0, 0, 0);
    const ofColor OLD_MAN = ofColor(200, 53, 19);
    const ofColor DUNGEON_GUARDS = ofColor(184,103, 181);
    const ofColor SHIELD_BLOCKER = ofColor(255, 201, 14);

    // Floors
    const ofColor WALKABLE_CAVE_FLOOR = ofColor(1, 0, 0);
    const ofColor WALKABLE_OVERWORLD_FLOOR = ofColor(255, 192, 122);
    const ofColor WATER_BRIDGE = ofColor(217, 78, 65);
    const ofColor WALKABLE_DUNGEON_FLOOR = ofColor(122,120,122);
};

struct EntityPixelColors{

    // Doors
    const ofColor OLD_MANS_CAVE_ENTRANCE = ofColor(0, 0, 1);
    const ofColor OVERWORLD_ENTRANCE = ofColor(0, 0, 2);
    //For consistency and ease, overworld pixel Map already has this door 
    //with this color in it, but it does not send you anywhere, 
    //that is where you come in :D
    const ofColor DUNGEON_ENTRANCE = ofColor(0, 0, 3);
    const ofColor FIRE_DUNGEON_ENTRANCE = ofColor(0, 0, 4);
    
    // StaticEntities
    const ofColor FIRE = ofColor(250, 134, 107);

    // DynamicEntities
    const ofColor LINK = ofColor(25, 255, 0);
};
