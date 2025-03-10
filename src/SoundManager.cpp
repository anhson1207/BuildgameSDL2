#include "SoundManager.hpp"
#include <iostream>
using namespace std;
SoundManager& SoundManager::GetInstance() {
    static SoundManager instance;
    return instance;
}
void SoundManager::LoadSounds() {
    soundLinked = Mix_LoadWAV("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/sounds/linked.wav");
    soundOho = Mix_LoadWAV("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/sounds/oho.wav");
    soundWin=Mix_LoadWAV("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/sounds/win.wav");
    soundLose=Mix_LoadWAV("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/sounds/no_move.wav");
    if (!soundLinked) {
       cout<< "Failed to load linked.wav: " << Mix_GetError() <<endl;
    }
    if (!soundOho) {
        cout<< "Failed to load oho.wav: " << Mix_GetError() <<endl;
    }
    if(!soundWin){
        cout<< "Failed to load win.wav: " << Mix_GetError() <<endl;
    }
    if(!soundLose){
        cout<< "Failed to load lose.wav: " << Mix_GetError() <<endl;
    }
}
void SoundManager::PlayLinkedSound() {
    if (soundLinked) {
        Mix_PlayChannel(-1, soundLinked, 0);
    }
}

void SoundManager::PlayOhoSound() {
    if (soundOho) {
        Mix_PlayChannel(-1, soundOho, 0);
    }
}
void SoundManager::PlayWinSound(){
    if(soundWin){
        Mix_PlayChannel(-1, soundWin, 0);
    }
}
void SoundManager::PlayLoseSound(){
    if(soundLose){
        Mix_PlayChannel(-1, soundLose, 0);
    }
}
void SoundManager::Cleanup() {
    if (soundLinked) {
        Mix_FreeChunk(soundLinked);
        soundLinked = nullptr;
    }
    if (soundOho) {
        Mix_FreeChunk(soundOho);
        soundOho = nullptr;
    }
    if (soundWin) {
        Mix_FreeChunk(soundWin);
        soundWin = nullptr;
    }
    if (soundLose) {
        Mix_FreeChunk(soundLose);
        soundLose = nullptr;
    }
}

