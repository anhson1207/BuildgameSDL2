#include "Score.hpp"
#include <iostream>
using namespace std;
const int scoreWidth=180;
const int scoreHeight=50;
const int font_Size=28;
const int colorR=145;
const int colorG=235;
const int colorB=247;
const int colorAlpha=255;
Score::Score(SDL_Renderer* renderer): score(0), renderer(renderer), texture(nullptr) {
    if (TTF_Init() == -1) {
        cout << "TTF_Init failed: " << TTF_GetError() << endl;
    }

    font = TTF_OpenFont("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/Roboto-VariableFont_wdth,wght.ttf", font_Size);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
    
    color = {colorR,colorG,colorB,colorAlpha};
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
        cout<< "Failed to render text surface: " << TTF_GetError() << endl;
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

    SDL_Rect scoreRect = {x, y, scoreWidth, scoreHeight};
    SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
}
void Score::resetScore(){
    score=0;
}
int Score::getScore(){
    return score;
}
