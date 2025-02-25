#include "main.hpp"
#include "graphics.hpp"
#include "board.hpp"
#include "GameScene.hpp"
#include <SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "TimeBar.hpp"
using namespace std;
bool isMouseOver(int mouseX,int mouseY,int x,int y,int w,int h){
    return (mouseX>=x&&mouseX<=x+w&&mouseY>=y&&mouseY<=y+h);
}

int main(int argc,char *argv[]){
    Graphics graphics;
    if(!graphics.init()){
        return -1;
    }
    SDL_Renderer* renderer = graphics.getRenderer();
    SDL_Color timeBarColor={255,255,255,255};
    TimeBar timeBar(100,50,600,30,30.0f,timeBarColor);
    
    ButtonEvent buttonEvent(renderer,ROW,COL);
    SDL_Texture *background=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground1.jpeg");
    SDL_Texture *playButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.png");
    SDL_Texture *guideButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/guide.png");
    SDL_Texture*guideImage=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/backgroundGuide.jpeg");
    SDL_Texture*closeButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/close.png");
    SDL_Texture*playImage=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground2.jpeg");
    SDL_Cursor *handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    
    
    bool running=true;
    bool showGuide=false;
    bool isPlaying=false;
    SDL_Event event;
    Uint32 lastTime=SDL_GetTicks();
    while(running){
        while (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT){
                running=false;
            }
            Uint32 currentTime=SDL_GetTicks();
            float deltaTime=(currentTime-lastTime)/1000.0f;
            lastTime=currentTime;
            timeBar.update(deltaTime);
            //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            timeBar.render(renderer);
            SDL_RenderPresent(renderer);
            if(timeBar.isTimeUp()) break;

            buttonEvent.handleEvent(event);
            int mouseX=event.button.x;
            int mouseY=event.button.y;
            bool hovering=false;
            if(event.type==SDL_MOUSEBUTTONDOWN){
                if(mouseX>=510 && mouseX<=730&&mouseY>=540&&mouseY<=650){
                    SDL_SetCursor(handCursor);
                    cout<<"Start game"<<endl;
                    isPlaying=true;
                }
                if(mouseX>=580&&mouseX<=665&&mouseY>=660&&mouseY<=735){
                    SDL_SetCursor(handCursor);
                    cout<<"Open guide"<<endl;
                    showGuide=true;
                }
                if(showGuide && mouseX>=1020&&mouseX<=1080&&mouseY>=70&&mouseY<=130){
                    SDL_SetCursor(handCursor);
                    cout<<"Close guide"<<endl;
                    showGuide=false;
                }
            }
                if(isMouseOver(mouseX, mouseY, 510, 540, 730, 710)||isMouseOver(mouseX, mouseY, 580, 660, 665, 735)||(showGuide&&isMouseOver(mouseX, mouseY, 870, 90, 930, 150))){
                    SDL_SetCursor(handCursor);
                    hovering = true;
                }
                if(!hovering){
                    SDL_SetCursor(arrowCursor);
                }
            }
            
            
            graphics.clear();
            graphics.renderTexture(background, 0, 0, 1200, 950);
            graphics.renderTexture(playButton, 510, 540, 220, 170);
            graphics.renderTexture(guideButton, 580, 660, 75, 75);
            if (showGuide) {
                graphics.renderTexture(guideImage, 150, 100, 900, 750);
                graphics.renderTexture(closeButton, 1020,70, 60, 60);
                
            }
            if(isPlaying){
                graphics.renderTexture(playImage, 0, 0, 1200, 950);
            }
            buttonEvent.renderBoard();
            graphics.present();
        }
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(playButton);
        SDL_DestroyTexture(guideButton);
        SDL_DestroyTexture(closeButton);
        return 0;
    }

