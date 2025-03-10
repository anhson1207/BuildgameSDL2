
#ifndef Score_hpp
#define Score_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Score {
private:
    int score;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Renderer* renderer;


public:
    Score(SDL_Renderer* renderer);
    ~Score();
    void addScore(int points);
    void render(int x, int y);
    void resetScore(){
        score=0;
    };
    int getScore();
    void updateTexture();

};


#endif /* Score_hpp */

