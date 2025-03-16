#include "TimeBar.hpp"
#include "constants.h"
using namespace std;
TimeBar::TimeBar(int x,int y,int width,int height,int totalTime,SDL_Color color){
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->totalTime=totalTime;
    this->color=color;
    this->startTime=SDL_GetTicks();
    this->isRunningTimeBar=false;
}
void TimeBar::start(){
    isRunningTimeBar = true;
    startTime=SDL_GetTicks();
}
void TimeBar::render(SDL_Renderer *renderer){
    if (!isRunningTimeBar) return;
    Uint32 elapsed=SDL_GetTicks()-startTime;
    float percent=1.0f-(float)elapsed/totalTime;
    if(percent<0) percent=0;
    int currentWidth=(int)(width*percent);
    SDL_Rect timeBar={x,y,currentWidth,height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,colorAlpha);
    SDL_RenderFillRect(renderer, &timeBar);
}
bool TimeBar::isTimeUp(){
    return (SDL_GetTicks()-startTime)>=totalTime;
}
