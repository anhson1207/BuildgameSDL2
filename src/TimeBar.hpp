
#ifndef TimeBar_hpp
#define TimeBar_hpp

#include <stdio.h>
#include <SDL.h>
class TimeBar{
private:
    int x,y;
    int width,height;
    int totalTime;
    Uint32 startTime;
    SDL_Color color;
    bool isRunningTimeBar;
public:
    TimeBar(int x,int y,int width,int height,int totalTime,SDL_Color color);
    void start();
    void update();
    void render(SDL_Renderer *renderer);
    bool isTimeUp();
};

#endif /* TimeBar_hpp */
