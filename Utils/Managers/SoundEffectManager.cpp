#include "SoundEffectManager.h"

void SoundEffectManager::update(){
    // Remove all sound effects that are no longer playing
    for(auto it = playingSounds.begin(); it != playingSounds.end();){
        if(!it->second->isPlaying()){
            it->second->stop();
            it = playingSounds.erase(it);
        }
        else
            it++;
    }
}

void SoundEffectManager::playSoundEffect(string fileName){
    if (isMuted()) return; // Don't play sound effects if muted

    string path = formatAudioPath(fileName);

    if (cache.find(path) != cache.end()) {

        // Sound is already playing, do not play again
        if (playingSounds.find(path) != playingSounds.end())
            return;

        ofSoundPlayer* sound = cache.at(path);
        playingSounds[path] = sound;
        sound->play();
    }
}

void SoundEffectManager::stopSoundEffect(string fileName){

    string path = formatAudioPath(fileName);

    if (playingSounds.find(path) != playingSounds.end()) {
        ofSoundPlayer* sound = playingSounds.at(path);
        sound->stop();
        playingSounds.erase(path);
    }
}

void SoundEffectManager::stopAllSoundEffects(){
    for(auto it = playingSounds.begin(); it != playingSounds.end();){
        it->second->stop();
        it = playingSounds.erase(it);
    }
}