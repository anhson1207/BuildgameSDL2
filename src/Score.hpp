
#ifndef Score_hpp
#define Score_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Score{
private:
    int score;
    TTF_Font *font;
    SDL_Color color;
public:
    Score();
    ~Score();
    void addScore(int points);
    void render(SDL_Renderer *renderer,int x,int y);
    int getScore() const;
};


#endif /* Score_hpp */
