# pragma once

#include "ofMain.h"
#include "AudioManager.h"
#include <map>
/**
 * The SoundEffectManager class is an object that manages all sound effects in the game.
 * 
 * On instantiation, the SoundEffectManager caches all audio located under data/sound_effects to 
 * improve performance throughout the game.
 * 
 * Multiple sound effects can be played at once, and the SoundEffectManager will keep track of them.
 */
class SoundEffectManager : public AudioManager{
    private:
        map<string, ofSoundPlayer*> playingSounds;   // A map of all the sound effects that are playing

    public:
        // Constructor
        SoundEffectManager() : AudioManager("audio/sound_effects") {};
        ~SoundEffectManager(){};

        // OF functions
        void update();

        // Sound effect functions
        void playSoundEffect(string fileName);      // Add a sound effect to the list
        void stopSoundEffect(string fileName);      // Stop the given sound effect
        void stopAllSoundEffects();

};