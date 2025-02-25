
#ifndef TimeBar_hpp
#define TimeBar_hpp

#include <stdio.h>
#include <SDL.h>
class TimeBar{
private:
    SDL_Rect barRect;
    SDL_Color barColor;
    int maxWidth;
    int height;
    float duration;
    float elapsedTime;
public:
    TimeBar(int x,int y,int width,int height,float duration,SDL_Color color);
    void update(float deltaTime);
    void render(SDL_Renderer * renderer);
    bool isTimeUp() const;
    void reset();
};

#endif /* TimeBar_hpp */
