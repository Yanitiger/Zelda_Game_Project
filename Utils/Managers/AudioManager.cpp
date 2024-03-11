#include <AudioManager.h>

AudioManager::AudioManager(string directoryPath){
    muted = false;
    this->pathPrefix = directoryPath;

    // Load all resources in the given path
    ofDirectory musicDir(directoryPath);
    musicDir.allowExt("wav");
    musicDir.listDir();

    for(int i = 0; i < musicDir.size(); i++){
        ofSoundPlayer* temp = new ofSoundPlayer();
        string p = musicDir.getPath(i);

        // Replace all backslashes with forward slashes
        // to avoid problems with Windows
        std::replace(p.begin(), p.end(), '\\', '/');

        temp->load(p);
        cache[p] = temp;
    }
        
    
}

string AudioManager::formatAudioPath(string fileName){
    // Check if the user was funny and forgot to add 
    // .wav at the end of the path

    if (fileName.find(".wav") == string::npos)
        fileName += ".wav";
    

    return this->pathPrefix + "/" + fileName;
}

AudioManager::~AudioManager(){

}