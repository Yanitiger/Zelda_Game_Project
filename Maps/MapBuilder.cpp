#include "MapBuilder.h"
#include <memory>

MapBuilder::MapBuilder(shared_ptr<Handler> handler) {
    this->handler = handler;
}

ofFbo MapBuilder::createFbo(ofImage pixelMap) {
    ofFbo mapFbo = ofFbo();

    // Allocate the fbo to the size of the resulting map
    // pixelMap.getWidth() = # of tiles in the x axis
    // pixelMap.getHeight() = # of tiles in the y axis
    mapFbo.allocate(pixelMap.getWidth() * Handler::TILE_WIDTH, pixelMap.getHeight() * Handler::TILE_HEIGHT);

    // Everything drawn from this point on will be drawn to the fbo
    mapFbo.begin();

    // Clear the fbo
    ofClear(255, 255, 255, 0);

    return mapFbo;
}

unique_ptr<Map> MapBuilder::createMap(ofImage pixelMap) {

    // Fields to be used in the map constructor
    shared_ptr<Link> linkPtr = nullptr;
    vector<vector<shared_ptr<Section>>> sections;
    int startingSectionX = 0;
    int startingSectionY = 0;
    bool foundLink = false;

    // Object that will "absorb" all the pixels we draw to it
    ofFbo mapFbo = createFbo(pixelMap);

    const int HORIZONTAL_COUNT = Handler::HORIZONTAL_TILE_COUNT;
    const int VERTICAL_COUNT = Handler::VERTICAL_TILE_COUNT;

    // This double for loop goes over the top left corner of each section
    // (0,0), (16, 0), (32, 0) ... (16*n, 0)
    // (0,11), (16, 11), (32, 11) ... (16*n, 11)
    // ...
    // (0,11*n), (16, 11*n), (32, 11*n) ... (16*n, 11*n)
    for (int pixelMapY = 0;
         pixelMapY + VERTICAL_COUNT - 1 < pixelMap.getHeight();
         pixelMapY += VERTICAL_COUNT) {
        vector<shared_ptr<Section>> sectionsRow;

        for (int pixelMapX = 0;
             pixelMapX + HORIZONTAL_COUNT - 1 < pixelMap.getWidth();
             pixelMapX += HORIZONTAL_COUNT) {
            shared_ptr<Section> section = createSection(pixelMapX, pixelMapY, linkPtr, pixelMap);

            // The first time we find link, set sectionX/sectionY
            if (linkPtr != nullptr && !foundLink) {
                // Divide by 16 or 11 to get the section
                // number we found link in :D
                startingSectionX = pixelMapX / HORIZONTAL_COUNT;
                startingSectionY = pixelMapY / VERTICAL_COUNT;
                foundLink = true;
            }
            sectionsRow.push_back(section);
        }
        sections.push_back(sectionsRow);
    }

    // Stop drawing to the fbo
    mapFbo.end();

    // Get the fbo as an image
    ofImage mapImage;
    ofPixels mapPixels;
    mapFbo.readToPixels(mapPixels);
    mapImage.setFromPixels(mapPixels);

    return make_unique<Map>(startingSectionX, startingSectionY, mapImage, linkPtr, sections);
}

shared_ptr<Section> MapBuilder::createSection(int startingPixelMapX, int startingPixelMapY, shared_ptr<Link> &linkPtr, ofImage pixelMap) {
    shared_ptr<Section> section = make_shared<Section>();
    const int HORIZONTAL_COUNT = Handler::HORIZONTAL_TILE_COUNT;
    const int VERTICAL_COUNT = Handler::VERTICAL_TILE_COUNT;

    // Relative Y tile position in the section
    int yOffset = startingPixelMapY % VERTICAL_COUNT;

    // This double for loop goes over all the pixels in the section
    // For example, assuming a starting coordinate of (x,y) and a section size of 16x11
    // (x,y), (x+1,y), (x+2,y) ... (x+15,y)
    // (x,y+1), (x+1,y+1), (x+2,y+1) ... (x+15,y+1)
    // ...
    // (x,y+10), (x+1,y+10), (x+2,y+10) ... (x+15,y+10)
    for (int y = startingPixelMapY; y < startingPixelMapY + VERTICAL_COUNT; y++) {

        // Relative X tile position in the section
        int xOffset = startingPixelMapX % HORIZONTAL_COUNT;

        for (int x = startingPixelMapX; x < startingPixelMapX + HORIZONTAL_COUNT; x++) {

            ofColor currentPixel = pixelMap.getColor(x, y);

            // OF Window Coordinates
            int windowXPos = xOffset * Handler::TILE_WIDTH;
            int windowYPos = yOffset * Handler::TILE_HEIGHT + Handler::GAME_SCREEN.y;

            if (currentPixel == entityPixelColors.LINK) {
                linkPtr = make_shared<Link>(
                    windowXPos,
                    windowYPos,
                    handler,
                    handler->getImageManager()->linkAnimations);

                // Set the current pixel to a floor tile
                // The rest of the statements will handle the drawing
                currentPixel = tilePixelColors.WALKABLE_OVERWORLD_FLOOR;
            }

            int column = -1;
            int row = -1;
            bool collidable = true;                // Default: Assume the block is collidable
            bool isADoor = false;                  // Default: Assume the block is not a door
            MapName whereTo = MapName::OVER_WORLD; // If it's a door, where does it lead to
            bool useEntitySheet = false;           // Default: Assume the block is not an entity

            // Central Mountain Wall
            if (currentPixel == tilePixelColors.CENTRAL_MOUNTAIN_WALL) {
                column = 7;
                row = 3;
            }
            // Walkable Over World Floor
            else if (currentPixel == tilePixelColors.WALKABLE_OVERWORLD_FLOOR) {
                column = 2;
                row = 0;
                collidable = false;
            }
            // Walkable Cave Floor
            else if (currentPixel == tilePixelColors.WALKABLE_CAVE_FLOOR) {
                column = 4;
                row = 1;
                collidable = false;
            }
            // Upper Mountain Wall
            else if (currentPixel == tilePixelColors.UPPER_MOUNTAIN_WALL) {
                column = 7;
                row = 2;
            }
            // Lower Right Mountain Corner
            else if (currentPixel == tilePixelColors.LOWER_RIGHT_MOUNTAIN_CORNER) {
                column = 8;
                row = 3;
            }
            // Lower Left Mountain Corner
            else if (currentPixel == tilePixelColors.LOWER_LEFT_MOUNTAIN_CORNER) {
                column = 6;
                row = 3;
            }
            // Upper Right Mountain Corner
            else if (currentPixel == tilePixelColors.UPPER_RIGHT_MOUNTAIN_CORNER) {
                column = 8;
                row = 2;
            }
            // Upper Left Mountain Corner
            else if (currentPixel == tilePixelColors.UPPER_LEFT_MOUNTAIN_CORNER) {
                column = 6;
                row = 2;
            }
            // Lower Left Brown Corner
            else if (currentPixel == tilePixelColors.LOWER_LEFT_BROWN_CORNER) {
                column = 0;
                row = 3;
            }
            // Lower Right Brown Corner
            else if (currentPixel == tilePixelColors.LOWER_RIGHT_BROWN_CORNER) {
                column = 2;
                row = 3;
            }
            // Upper Left Brown Corner
            else if (currentPixel == tilePixelColors.UPPER_LEFT_BROWN_CORNER) {
                column = 0;
                row = 2;
            }
            // Upper Right Brown Corner
            else if (currentPixel == tilePixelColors.UPPER_RIGHT_BROWN_CORNER) {
                column = 2;
                row = 2;
            }
            // Upper Brown Wall
            else if (currentPixel == tilePixelColors.UPPER_BROWN_WALL) {
                column = 1;
                row = 2;
            }
            // Green Trees
            else if (currentPixel == tilePixelColors.GREEN_TREES) {
                column = 7;
                row = 1;
            }
            // Central Water
            else if (currentPixel == tilePixelColors.CENTRAL_WATER) {
                column = 1;
                row = 5;
            }
            // Green Snail Bush Things
            else if (currentPixel == tilePixelColors.GREEN_SNAIL_BUSH_THINGS) {
                column = 7;
                row = 0;
            }
            // Central Brown Wall
            else if (currentPixel == tilePixelColors.CENTRAL_BROWN_WALL) {
                column = 1;
                row = 3;
            }
            // Brown Snail Rock Thing
            else if (currentPixel == tilePixelColors.BROWN_SNAIL_ROCK_THING) {
                column = 1;
                row = 0;
            }
            // Water down-left corner
            else if (currentPixel == tilePixelColors.WATER_LOWER_LEFT_CORNER) {
                column = 0;
                row = 6;
            }
            // Water Bridge
            else if (currentPixel == tilePixelColors.WATER_BRIDGE) {
                column = 5;
                row = 7;
                collidable = false;
            }
            // Black Entrance
            else if (currentPixel == tilePixelColors.BLACK_ENTRANCE) {
                column = 4;
                row = 1;
            }
            // Cave Wall
            else if (currentPixel == tilePixelColors.CAVE_WALL) {
                column = 18;
                row = 1;
            }
            // Cave Upper Wall
            else if (currentPixel == tilePixelColors.CAVE_UPPER_WALL) {
                column = 18;
                row = 0;
            }
            //Shield Blocker
            else if (currentPixel == tilePixelColors.SHIELD_BLOCKER) {
                column = 2;
                row = 1;
            }
// --------------------------------- Phase 3 -> New Dungeon ---------------------------------------------
            // Dungeon Blocks and Decoration
            else if(currentPixel == tilePixelColors.WALKABLE_DUNGEON_FLOOR) {
                column = 14;
                row = 0;
                collidable = false;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_FISH) {
                column = 5;
                row = 9;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_DRAGON) {
                column = 5;
                row = 10;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_WALL) {
                column = 13;
                row = 3;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_ENTRANCE_LEFT) {
                column = 15;
                row = 3;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_ENTRANCE_LEFT_UP) {
                column = 15;
                row = 2;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_ENTRANCE_RIGHT) {
                column = 17;
                row = 3;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_ENTRANCE_RIGHT_UP) {
                column = 17; 
                row = 2;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_HALF_LEFT_FLOOR) {
                column = 14; 
                row = 7;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_HALF_RIGHT_FLOOR) {
                column = 15; 
                row = 7;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_WATER) {
                column = 13;
                row = 5;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_FALLING_WATER) {
                column = 16;
                row = 7;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_GUARDS) {
                column = 14;
                row = 1;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_UP_ARROW) {
                column = 6;
                row = 9; 
                collidable = true;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_DOWN_ARROW) {
                column = 7;
                row = 9; 
                collidable = true;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_LEFT_ARROW) {
                column = 0;
                row = 10; 
                collidable = true;
            }
            else if(currentPixel == tilePixelColors.DUNGEON_RIGHT_ARROW) {
                column = 1;
                row = 10; 
                collidable = true;
            }
            // Old Man (he is a wall :()
            else if (currentPixel == tilePixelColors.OLD_MAN) {
                column = 10;
                row = 3;
                useEntitySheet = true; // this is here so that we get the old man image
            }
            // Fire
            else if (currentPixel == entityPixelColors.FIRE) {
                column = 4;
                row = 5;
                useEntitySheet = true;
                collidable = true;
            }
            // OldMan's Cave Entrance
            else if (currentPixel == entityPixelColors.OLD_MANS_CAVE_ENTRANCE) {
                column = 4;
                row = 1;
                isADoor = true;
                whereTo = MapName::OLD_MANS_CAVE;
            }
             // Dunegon's Entrance
            else if (currentPixel == entityPixelColors.DUNGEON_ENTRANCE) {
                column = 4;
                row = 1;
                isADoor = true;
                whereTo = MapName::DUNGEON;
            }
            // Exit towards the OverWorld
            else if (currentPixel == entityPixelColors.OVERWORLD_ENTRANCE) {
                column = 4;
                row = 1;
                isADoor = true;
                whereTo = MapName::OVER_WORLD;
            }
            else if (currentPixel == entityPixelColors.FIRE_DUNGEON_ENTRANCE) {
                column = 4;
                row = 1;
                isADoor = true;
                whereTo = MapName::FIRE_DUNGEON;
            }
            // Pixel Color Not Found (RIP)
            else {
                column = 13;
                row = 1;
            }

            ofImage blockImage = useEntitySheet ? 
                handler->getImageManager()->getSpriteFromEntitySheetAt(column, row) : 
                handler->getImageManager()->getSpriteFromMapSheetAt(column, row);

            // Save block to the FBO
            blockImage.draw(
                x * Handler::TILE_WIDTH,  // Absolute Pixel Position
                y * Handler::TILE_HEIGHT, // Absolute Pixel Position
                Handler::TILE_WIDTH,      // Width
                Handler::TILE_HEIGHT      // Height
            );

            if (collidable) // We found a block that is collidable; add it to the section
            {
                shared_ptr<StaticEntity> block;
                if (isADoor) // Oh shoot, it's a door instead
                {
                    block = make_shared<DoorBlock>(windowXPos, windowYPos, handler, whereTo);
                    // Save the coordinates of this door so that Link can use
                    // them later to set his X and Y when changing maps
                    // DISCLAIMER: This only works properly IF and only IF there's one door per section.
                    //             Due to the nature of the nested for loop, If there's more than one door,
                    //             this will grab the door last created door, aka the lowest to the right
                    section->doorXPos = windowXPos;
                    section->doorYPos = windowYPos;
                }

                else if (currentPixel == entityPixelColors.FIRE)// FIRE
                {
                    block = make_shared<Fire>(windowXPos, windowYPos, handler);
                } 
                else if (currentPixel == tilePixelColors.DUNGEON_UP_ARROW) {

                    block = make_shared<ArrowUpDirection>(windowXPos, windowYPos, handler);
                } else if (currentPixel == tilePixelColors.DUNGEON_DOWN_ARROW) {

                    block = make_shared<ArrowDownDirection>(windowXPos, windowYPos, handler);
                } else if (currentPixel == tilePixelColors.DUNGEON_LEFT_ARROW) {

                    block = make_shared<ArrowLeftDirection>(windowXPos, windowYPos, handler);
                } else if (currentPixel == tilePixelColors.DUNGEON_RIGHT_ARROW) {
                    
                    block = make_shared<ArrowRightDirection>(windowXPos, windowYPos, handler);
                } else if (currentPixel == tilePixelColors.SHIELD_BLOCKER) {

                    block = make_shared<ShieldBlock>(windowXPos, windowYPos, handler);
                }
                else // nvm it's just a regular block
                {
                    block = make_shared<BoundBlock>(windowXPos, windowYPos, handler);
                }
                section->addBlockToPosition(xOffset, yOffset, block);
            }
            xOffset++;
        }
        yOffset++;
    }
    return section;
}
