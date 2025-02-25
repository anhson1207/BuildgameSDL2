#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class GameScene {
public:
    GameScene(SDL_Renderer* renderer);
    ~GameScene();

    void showProgressTimer();
    void updateProgressTimer(float deltaTime);
    void renderProgressTimer();

private:
    SDL_Renderer* renderer;
    SDL_Texture* progressBarTexture;
    SDL_Rect progressBarFullRect;
    SDL_Rect progressBarCurrentRect;
    float progressPercentage;
    float totalTime;
    float elapsedTime;
};


#endif
