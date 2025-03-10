

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <string>
class SoundManager {
public:
    static SoundManager& GetInstance();
    void LoadSounds();
    void PlayLinkedSound();
    void PlayOhoSound();
    void Cleanup();
private:
    SoundManager() = default;
    ~SoundManager() = default;
    Mix_Chunk* soundLinked = nullptr;
    Mix_Chunk* soundOho = nullptr;

};

#endif 

