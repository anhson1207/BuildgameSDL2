#include "TimeBar.hpp"
TimeBar::TimeBar(int x,int y,int width,int height,float duration,SDL_Color color){
    barRect={x,y,width,height};
    barColor=color;
    maxWidth=width;
    this->height=height;
    this->duration=duration;
    elapsedTime=0.0f;
}
void TimeBar::update(float deltaTime){
    elapsedTime+=deltaTime;
    if(elapsedTime>duration) elapsedTime=duration;
    barRect.w=static_cast<int>(maxWidth*(1-elapsedTime/duration));
}
void TimeBar::render(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
    SDL_RenderFillRect(renderer, &barRect);
}
bool TimeBar::isTimeUp() const{
    return elapsedTime>=duration;
}
void TimeBar::reset(){
    elapsedTime=0.0f;
    barRect.w=maxWidth;
}
