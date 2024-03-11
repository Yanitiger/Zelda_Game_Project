#include "Section.h"

Section::Section() {

    for (int y = 0; y < Handler::VERTICAL_TILE_COUNT; y++) {
        vector<shared_ptr<StaticEntity>> currBlocks;
        vector<shared_ptr<Item>> currItems;
        // fill funny with x nullptrs
        for (int x = 0; x < Handler::HORIZONTAL_TILE_COUNT; x++) {
            currBlocks.push_back(nullptr);
            currItems.push_back(nullptr);
        }

        blocks.push_back(currBlocks);
        items.push_back(currItems);
    }
};
void Section::update() {
    // Tick all enemies
    for (shared_ptr<DynamicEntity> enemy : enemies){
        if (!enemy->isDead()){
             enemy->update();
        }
    }
        
    // for(auto row : items) {
    //     for(auto block : row) {
    //         if(block->getIsCollected()){
    //             deleteItem(block);
    //         }
    //     }
    // }

    // Blocks don't need to be ticked unless
    // they have an animation
}

void Section::draw(){

    // If DEBUG mode is on, draw the hitboxes of all blocks
    if (Handler::DEBUG){
        for(int i = 0; i < blocks.size(); i++){
            for(int j = 0; j < blocks[i].size(); j++){
                shared_ptr<StaticEntity> block = blocks[i][j];
                if(blocks[i][j] != NULL){
                    ofNoFill();
                    ofSetLineWidth(Handler::PIXEL_SCALE);     
                    if (dynamic_pointer_cast<DoorBlock>(block) != nullptr)
                        ofSetColor(ofColor::purple);
                    
                    else
                        ofSetColor(ofColor::white);

                    ofDrawRectangle(blocks[i][j]->getBounds());
                    //Clear the color
                    ofSetColor(255,255,255);
                }
            }
        }
    }
    if(!transtioning){
        for (int i = 0; i < items.size(); i++) {
            for (int j = 0; j < items[i].size(); j++) {
                if (items[i][j] != NULL)
                    items[i][j]->draw();
            }
        }

        for (int i = 0; i < enemies.size(); i++){
            if (enemies[i] != NULL && !enemies[i]->isDead())
                enemies[i]->draw();
        }
    }
}

void Section::respawnEnemies() {
    for (shared_ptr<DynamicEntity> enemy : enemies){
        enemy->revive();
    }
}

/* ---------------------------------------- Phase 1 -> Delete the sword created -----------------------------------------*/
/* We call this methos in order to delete the Items of the section once they are pick Up by Link. Nice :)*/
void Section::deleteItem(shared_ptr<Item> item) {
    bool found = false;
    for (auto row = items.begin(); row != items.end(); row++){
        if (found == false) {
            for (auto it = row->begin(); it != row->end(); it++){
                if (*it == item){
                    row->erase(it);
                    found = true;
                }
            }
        }
    }
}

void Section::deleteBlock(shared_ptr<StaticEntity> block) {
    bool found = false;
    for (auto row = blocks.begin(); row != blocks.end(); row++){
        if (found == false) {
            for (auto it = row->begin(); it != row->end(); it++){
                if (*it == block){
                    row->erase(it);
                    found = true;
                }
            }
        }
    }
}