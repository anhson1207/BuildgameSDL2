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

    if (!soundLinked) {
       cout<< "Failed to load linked.wav: " << Mix_GetError() <<endl;
    }
    if (!soundOho) {
        cout<< "Failed to load oho.wav: " << Mix_GetError() <<endl;
    }
}
void SoundManager::PlayLinkedSound() {
    if (soundLinked) {
        Mix_PlayChannel(-1, soundLinked, 0);
    }
}

// Phát âm thanh khi Pokémon không hợp lệ hoặc chọn cùng 1 con
void SoundManager::PlayOhoSound() {
    if (soundOho) {
        Mix_PlayChannel(-1, soundOho, 0);
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
}

