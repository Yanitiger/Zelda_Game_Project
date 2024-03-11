#pragma once

#include "Direction.h"
#include "ImageManager.h"
#include "MusicManager.h"
#include "SoundEffectManager.h"
#include "ofMain.h"
#include <memory>

using namespace std;

/**
 * A High-level class that contains all the managers and constants.
 *
 * Through this class, we can access the managers and constants from anywhere in the code,
 * without having to:
 * * Pass the managers as parameters to the constructors of the classes that need them
 * * Relying on global variables
 * * Depend on ofApp.h
 *
 * This allows ofApp and the states to have access to the same things
 *
 */
class Handler {
private:
    unique_ptr<SoundEffectManager> soundEffectManager;
    unique_ptr<ImageManager> imageManager;
    unique_ptr<MusicManager> musicManager;

public:
    Handler(unique_ptr<SoundEffectManager> soundEffectManager, unique_ptr<ImageManager> imageManager, unique_ptr<MusicManager> musicManager) {
        this->soundEffectManager = move(soundEffectManager);
        this->imageManager = move(imageManager);
        this->musicManager = move(musicManager);
        this->DEBUG = false;
    }

    const unique_ptr<SoundEffectManager> &getSoundEffectManager() { return soundEffectManager; }
    const unique_ptr<ImageManager> &getImageManager() { return imageManager; }
    const unique_ptr<MusicManager> &getMusicManager() { return musicManager; }

    // Constants
    static const int PIXEL_SCALE = 3;               // By how much we scale the pixels
    static const int HORIZONTAL_TILE_COUNT = 16;    // How many tiles are in a section, horizontally. Units: tiles
    static const int VERTICAL_TILE_COUNT = 11;      // How many tiles are in a section, vertically. Units: tiles
    static const int VERTICAL_HUD_TILE_COUNT = 3;   // How many tiles are in the HUD, vertically. Units: tiles

    // Derived constants
    static const int TILE_WIDTH = 16 * PIXEL_SCALE;                         // How many pixels are in a tile, horizontally. Units: pixels/tile
    static const int TILE_HEIGHT = 16 * PIXEL_SCALE;                        // How many pixels are in a tile, vertically    Units: pixels/tile
    static const int SECTION_WIDTH = HORIZONTAL_TILE_COUNT * TILE_WIDTH;    // How many pixels are in a section, horizontally. Units: pixels/section
    static const int SECTION_HEIGHT = VERTICAL_TILE_COUNT * TILE_HEIGHT;    // How many pixels are in a section, vertically. Units: pixels/section
    static const int HUD_HEIGHT = VERTICAL_HUD_TILE_COUNT * TILE_HEIGHT;    // How many pixels are in the HUD, vertically. Units: pixels
    static ofRectangle GAME_SCREEN;                                         // The rectangle that represents the game screen
    static ofRectangle HUD_SCREEN;                                          // The rectangle that represents the HUD screen
    static bool DEBUG;                                                      // Whether the game is in debug mode or not
};