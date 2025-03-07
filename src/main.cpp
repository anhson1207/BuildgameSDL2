#include "main.hpp"
#include "graphics.hpp"
#include "board.hpp"
#include "GameScene.hpp"
#include <SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "TimeBar.hpp"
#include "Score.hpp"
#include <SDL2/SDL_ttf.h>
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
    SDL_Color colorTimeBar={120,255,255,255};
    TimeBar timeBar(300,100,600,30,300000,colorTimeBar);
    Score _score(renderer);
    ButtonEvent buttonEvent(renderer,ROW,COL,&_score);
    SDL_Texture *background=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground1.jpeg");
    SDL_Texture *playButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.png");
    SDL_Texture *guideButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/guide.png");
    SDL_Texture*guideImage=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/backgroundGuide.jpeg");
    SDL_Texture*closeButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/close.png");
    SDL_Texture*playImage=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground2.jpeg");
    SDL_Texture*timeIcon=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/time.png");
    SDL_Cursor *handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    
    
    bool running=true;
    bool showGuide=false;
    bool isPlaying=false;
    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT){
                running=false;
            }
           
            buttonEvent.handleEvent(event);
            int mouseX=event.button.x;
            int mouseY=event.button.y;
            bool hovering=false;
            if(event.type==SDL_MOUSEBUTTONDOWN){
                if(mouseX>=510 && mouseX<=730&&mouseY>=540&&mouseY<=650){
                    SDL_SetCursor(handCursor);
                    cout<<"Start game"<<endl;
                    isPlaying=true;
                    timeBar.start();
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
                graphics.renderTexture(timeIcon, 240, 95, 40, 40);
                _score.render(30, 30);
            }
        
            
        
        timeBar.render(renderer);
        
        buttonEvent.renderBoard();
        graphics.present();
        }
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(playButton);
        SDL_DestroyTexture(guideButton);
        SDL_DestroyTexture(closeButton);
        return 0;
    }

