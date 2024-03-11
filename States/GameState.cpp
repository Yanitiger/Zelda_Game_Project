#include "GameState.h"

void GameState::update()
{
    if(!paused){
        this->currentMap->update();
    }
    

    if(currentMap->isFinished()){
        currentMap->setFinished(false);
        if(currentMap->getWhereTo() == OVER_WORLD){
            //Set Link's X and Y coordinates relative to the coming map section's door positon
            currentMap->getPlayer()->setX(overWorldMap->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(overWorldMap->getCurrentSection()->doorYPos + Handler::TILE_HEIGHT);
            //TODO: Remove Link from being part of the Map to avoid multiple Links in diff maps.
            // For now we use the setter to have the same link in both maps
            overWorldMap->setPlayer(currentMap->getPlayer());
            currentMap = overWorldMap;
        }
        else if(currentMap->getWhereTo() == OLD_MANS_CAVE){
            currentMap->getPlayer()->setX(oldManCaveMap->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(oldManCaveMap->getCurrentSection()->doorYPos - Handler::TILE_HEIGHT);
            oldManCaveMap->setPlayer(currentMap->getPlayer());
            currentMap = oldManCaveMap;
        }
        else if(currentMap->getWhereTo() == DUNGEON) {
            currentMap->getPlayer()->setX(hiddenDungeon->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(hiddenDungeon->getCurrentSection()->doorYPos - Handler::TILE_HEIGHT);
            hiddenDungeon->setPlayer(currentMap->getPlayer());
            currentMap = hiddenDungeon;
        }
        else if(currentMap->getWhereTo() == FIRE_DUNGEON) {
            currentMap->getPlayer()->setX(fireDungeon->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(fireDungeon->getCurrentSection()->doorYPos - Handler::TILE_HEIGHT);
            fireDungeon->setPlayer(currentMap->getPlayer());
            currentMap = fireDungeon;
        }
    }

}

void GameState::draw() {
    ofSetColor(255, 255, 255);
    currentMap->draw();

    // Change to Game Over
    if (currentMap->getPlayer()->isDead()) {
        ofImage gameOver = handler->getImageManager()->gameOverScreen;
        gameOver.draw(0, 0, ofGetWidth(), ofGetHeight());
        changeState++;
        if (changeState == 120) {
            this->setFinished(true);
            this->setNextState(GAME_OVER);
        }
    }

    if (paused) {
        // Full Screen HUD Transition Parameters
        hudHeight <= ofGetHeight() ? hudHeight += Handler::PIXEL_SCALE*2 : hudHeight;
        hudH <= 0 ? hudH += Handler::PIXEL_SCALE*2 : hudH;

    } else {
        // Small Screen HUD Transition Parameters
        hudHeight > ofGetHeight()/4 ? hudHeight -= Handler::PIXEL_SCALE*2 : hudHeight;
        hudH > -Handler::SECTION_HEIGHT ? hudH -= Handler::PIXEL_SCALE*2 : hudH;
    }
    handler->getImageManager()->HUD.draw(0, hudH, ofGetWidth(), ofGetHeight());

    // Draw hearts on the HUD
    this->currentMap->getPlayer()->drawHearts(hudHeight-10);

    /*-------------------------------------------------------------------------------------------------------------------------------*/
    //                      Check if Link has collided with a weapon, if he has then draw it in the HUD
    // For the Sword, he will check if the Potion has been consumed, if its treu then draw the red sword, else draw the regular sword

    if(oldManCaveMap->getColliedSword() == true || swordCollected == true) {
        if(fireDungeon->getPowerActivation() == true) {
            handler->getImageManager()->redSword.draw(ofGetWidth()/2 - (ofGetWidth() % 10), hudHeight - 90, 40, 40);
        } else 
            handler->getImageManager()->basicSword.draw(ofGetWidth()/2 - (ofGetWidth() % 10), hudHeight - 90, 40, 40);
        
        swordCollected = true;
    }
    if(hiddenDungeon->getColliedStaff() == true || staffCollected == true) {
        handler->getImageManager()->magicStaff.draw(ofGetWidth()/2 + 65, hudHeight - 90, 40, 40);
        staffCollected = true;
    }

    // MiniMap
    ofDrawRectangle(this->currentMap->getPlayer()->getX()/20 + 40 * (currentMap->getCurrentSectionX()+1),  
                    hudHeight + (this->currentMap->getPlayer()->getY()/15  + 50 * (currentMap->getCurrentSectionY()+1)) - 175, 5, 5);
}

void GameState::reset() {

    this->musicFileName = "overworld.wav";
    mapBuilder = make_unique<MapBuilder>(handler);
    overWorldMap = mapBuilder->createMap(handler->getImageManager()->overWorldPixelMap);
    oldManCaveMap = mapBuilder->createMap(handler->getImageManager()->oldMansCavePixelMap);
    hiddenDungeon = mapBuilder->createMap(handler->getImageManager()->dungeonPixelMap);
    fireDungeon = mapBuilder->createMap(handler->getImageManager()->secondDungeonPixelMap);

    //If there's more than one section in a map, besides overWorld, we must set which section we want to start at
    hiddenDungeon->setCurrentSection(0,1);
    fireDungeon->setCurrentSection(0,1);
    oldManCaveMap->setCurrentSection(0,0);


    /* Items added on the Old Mans Cave */
    oldManCaveMap->getCurrentSection()->addItemToTile(6,4, createSword());

    /* Items/Enemys added on the hidden Dungeon */
    hiddenDungeon->getSection(0,0)->addItemToTile(7, 2, createStaff());
    hiddenDungeon->getSection(0, 1)->addItemToTile(6, 1, createFood());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(4, 7, createDungeonTektike());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(4, 5, createDungeonTektike());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(11, 7, createDungeonTektike());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(7, 6, createDungeonTektike());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(8, 6, createDungeonTektike());
    hiddenDungeon->getSection(0, 0)->addEnemyToTile(11, 5, createDungeonTektike());
    hiddenDungeon->getSection(0, 1)->addEnemyToTile(13, 5, createDungeonTektike());
    hiddenDungeon->getSection(0, 1)->addEnemyToTile(14, 4, createDungeonTektike());

    /* Items/Enemys added on the Fire Dungeon */
    fireDungeon->getSection(0, 0)->addItemToTile(7, 4, createPotion());
    fireDungeon->getSection(0, 1)->addEnemyToTile(7, 4, createTektike());

    /* Items/Enemys added on the Over World */
    overWorldMap->getSection(4, 1)->addItemToTile(13, 5, createShield());
    overWorldMap->getSection(1, 0)->addItemToTile(11, 5, createFood());
    overWorldMap->getSection(3, 1)->addItemToTile(6, 8, createFood());
    overWorldMap->getSection(0, 1)->addItemToTile(10, 4, createFood());
    overWorldMap->getSection(2, 0)->addEnemyToTile(8, 4, createTektike());
    overWorldMap->getSection(2, 0)->addEnemyToTile(4, 4, createTektike());
    overWorldMap->getSection(3, 1)->addEnemyToTile(7, 4, createTektike());
    overWorldMap->getSection(4, 1)->addEnemyToTile(7, 3, createBoss());

    currentMap = overWorldMap;

    paused = false;
    swordCollected = false;
    staffCollected = false;
    hudH = -Handler::SECTION_HEIGHT;
    hudHeight = Handler::HUD_HEIGHT;
    changeState = 0;
}

void GameState::keyPressed(int key) {
    if (key == 'p'){
        paused = !paused;
    } else {
        currentMap->keyPressed(key);
    }
}

void GameState::keyReleased(int key) {
    currentMap->keyReleased(key);
}
/*---------------------------------------------------------------------------------------------*/
/* Here we create all the animations for the Items/Enemys that we are going to add to the game */
shared_ptr<Tektike> GameState::createTektike() {
    // getTekitkeAnimations() returns a NEW shared_ptr
    // This is so that all Tektikes will not point
    // to the same animation object and "super tick" 
    // each other
    return make_shared<Tektike>(0, 0, handler, handler->getImageManager()->getTektikeAnimations());
}

shared_ptr<Boss> GameState::createBoss() {
    
    return make_shared<Boss>(0, 0, handler, handler->getImageManager()->getBossAnimations());
}

shared_ptr<Tektike> GameState::createDungeonTektike() {

    return make_shared<Tektike>(0, 0, handler, handler->getImageManager()->getDungeonTektikeAnimations());
}

shared_ptr<Sword> GameState::createSword() {

    return make_shared<Sword>(0 ,0 , handler, handler->getImageManager()->basicSword);

}
shared_ptr<MagicStaff> GameState::createStaff() {

    return make_shared<MagicStaff>(0 ,0 , handler, handler->getImageManager()->magicStaff);

}
shared_ptr<Food> GameState::createFood() {

    return make_shared<Food>(0 ,0 , handler, handler->getImageManager()->foodHeal);

}
shared_ptr<Shield> GameState::createShield() {

    return make_shared<Shield>(0 ,0 , handler, handler->getImageManager()->shield);

}
shared_ptr<PowerPotion> GameState::createPotion() {

    return make_shared<PowerPotion>(0 ,0 , handler, handler->getImageManager()->potion);

}
