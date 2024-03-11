
#pragma once

#include "ofMain.h"
#include "AudioManager.h"
#include <map>

/**
 * The MusicManager class is an object that manages all music in the game.
 * 
 * On instantiation, the MusicManager caches all audio located under data/music to 
 * improve performance throughout the game.
 * 
 * Only one track can be played at a time. If a new track is played, the old track
 * will stop playing.
 * 
*/
class MusicManager : public AudioManager{
    private:
        ofSoundPlayer* currentTrack;                 // The current track that is playing

    public:
        // Constructor
        MusicManager();
        ~MusicManager();

        // OF functions
        void update();

        // Music functions
        void playMusic(string fileName);    // Play the loaded track from the beginning
        void stopMusic();               // Stop the loaded track
        void resumeMusic();             // Resume the loaded track
        void pauseMusic();              // Pause the loaded track

        // Alias functions
        void unmute();
        void mute();

        // Getters and setters
        ofSoundPlayer& getMusic() { return *currentTrack;};
};