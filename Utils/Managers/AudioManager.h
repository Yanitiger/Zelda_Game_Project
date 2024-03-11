#pragma once

#include "ofMain.h"
#include <map>

/**
 * Utility Class to be extended by Managers that handle some kind of audio
 * (such as music or sound effects).
 * 
 * These two are handled separately because they have different use cases.
 * Music can only play one track at a time, while sound effects can play
 * multiple at once. This changes the logic of how they are handled.
 */
class AudioManager{
    protected:
        // Cache of all the sounds; This is to avoid loading the same sound multiple times
        map<string, ofSoundPlayer*> cache;

        bool muted;
        string pathPrefix; // The path prefix to the folder where the audio files are stored
        string formatAudioPath(string path);

    public:
        // Constructor
        AudioManager(string directoryPath);
        ~AudioManager();

        // OF functions
        virtual void update() = 0;

        // Getters and setters
        bool isMuted() const { return muted; }
        void setMuted(bool muted) { this->muted = muted;};
};