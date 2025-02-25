#include "GameScene.hpp"
GameScene::GameScene(SDL_Renderer* renderer)
    : renderer(renderer), progressPercentage(100.0f), totalTime(60.0f), elapsedTime(0.0f) {
   
    SDL_Surface* surface = IMG_Load("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/timeBar.jpeg");
    progressBarTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    progressBarFullRect = {100, 50, 600, 30};
    progressBarCurrentRect = progressBarFullRect;
}


GameScene::~GameScene() {
    SDL_DestroyTexture(progressBarTexture);
}
void GameScene::showProgressTimer() {
    progressPercentage = 100.0f;
    elapsedTime = 0.0f;
    progressBarCurrentRect.w = progressBarFullRect.w;
}
void GameScene::updateProgressTimer(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime > totalTime) elapsedTime = totalTime;
    progressPercentage = 100.0f * (1.0f - elapsedTime / totalTime);
    progressBarCurrentRect.w = static_cast<int>(progressBarFullRect.w * (progressPercentage / 100.0f));
}
void GameScene::renderProgressTimer() {
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &progressBarFullRect);
    SDL_RenderCopy(renderer, progressBarTexture, nullptr, &progressBarCurrentRect);
}


