#include "Score.hpp"
#include <iostream>
Score::Score(SDL_Renderer* renderer): score(0), renderer(renderer), texture(nullptr) {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/Roboto-VariableFont_wdth,wght.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    
    color = {145, 235, 247, 255};
    updateTexture();
}

Score::~Score() {
    if (texture) SDL_DestroyTexture(texture);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
}

void Score::updateTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    std::string scoreText = "SCORE: " + std::to_string(score);
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Score::addScore(int points) {
    score += points;
    updateTexture();
}

void Score::render(int x, int y) {
    if (!texture) return;

    SDL_Rect scoreRect = {x, y, 180, 50};
    SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
}
void Score::resetScore(){
    score=0;
}
int Score::getScore(){
    return score;
}
