#include "MusicManager.h"

MusicManager::MusicManager() : AudioManager("audio/music"){
    currentTrack = nullptr;
}

MusicManager::~MusicManager(){

}

void MusicManager::update(){

}

void MusicManager::playMusic(string fileName){

    string path = formatAudioPath(fileName);

    if (cache.find(path) != cache.end()) {
        stopMusic(); 
        currentTrack = cache.at(path);
        currentTrack->setLoop(true); // Loop the track by default

        if (!isMuted())
            currentTrack->play();
    }
}

void MusicManager::stopMusic(){
    if (currentTrack != nullptr && currentTrack->isPlaying())
        currentTrack->stop();

    currentTrack = nullptr;
}      

void MusicManager::resumeMusic(){
    if (currentTrack != nullptr && !isMuted())
        currentTrack->setPaused(false);
}

void MusicManager::pauseMusic(){
    if (currentTrack != nullptr)
        currentTrack->setPaused(true);
}

void MusicManager::unmute(){
    setMuted(false);
    resumeMusic();
}

void MusicManager::mute(){
    pauseMusic();
    setMuted(true);
}

