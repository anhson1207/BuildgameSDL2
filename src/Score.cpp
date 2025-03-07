#include <iostream>
#include "Score.hpp"
Score::Score():score(0){
    font=TTF_OpenFont("/Users/nguyenanhson/Documents/BuildgameSDL2/BigShoulders-VariableFont_opsz,wght.ttf", 28);
    color={145,235,247,255};
}
Score::~Score(){
    TTF_CloseFont(font);
}
void Score::addScore(int points){
    score+=points;
}
int Score::getScore() const{
    return score;
}
//void Score::render(SDL_Renderer*renderer,int x,int y){
//    std::string scoreText="SCORE: "+std::to_string(score);
//    SDL_Surface *surface=TTF_RenderText_Solid(font, scoreText.c_str(), color);
//    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_Rect scoreRect = {50, 50, surface->w, surface->h};
//    SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
//    SDL_FreeSurface(surface);
//    SDL_DestroyTexture(texture);
//}
void Score::render(SDL_Renderer* renderer, int x, int y) {
    std::string scoreText = "SCORE: " + std::to_string(score);

    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect scoreRect = {50, 50, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &scoreRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

