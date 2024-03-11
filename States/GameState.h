#pragma once

#include "Animation.h"
#include "Link.h"
#include "Tektike.h"
#include "MapBuilder.h"
#include "State.h"
#include "Boss.h"
#include <memory>

class GameState : public State {

private:
    shared_ptr<Map> currentMap;
    shared_ptr<Map> overWorldMap;
    shared_ptr<Map> oldManCaveMap;
    shared_ptr<Map> hiddenDungeon;
    shared_ptr<Map> fireDungeon;
    unique_ptr<MapBuilder> mapBuilder;
   
public:
    GameState(shared_ptr<Handler> handler) : State(handler) { this->reset(); }
    void update();
    void draw();
    void reset();
    void keyPressed(int key);
    void keyReleased(int key);
    ofImage menuHUD;
    bool paused;
    int hudY;
    int hudH;
    int hudHeight;
    int changeState;

    shared_ptr<Tektike> createTektike();
    shared_ptr<Boss> createBoss();
    shared_ptr<Tektike> createDungeonTektike();
    shared_ptr<Sword> createSword();
    shared_ptr<PowerPotion> createPotion();
    shared_ptr<MagicStaff> createStaff();
    shared_ptr<Food> createFood();
    shared_ptr<Shield> createShield();
    string weapon;
    void setWeapon(string name) {
        weapon = name;
    }
    bool swordCollected = false;
    bool staffCollected = false;
};