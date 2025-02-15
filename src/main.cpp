
#include "main.hpp"
#include "graphics.hpp"
#include <SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
bool isMouseOver(int mouseX,int mouseY,int x,int y,int w,int h){
    return (mouseX>=x&&mouseX<=x+w&&mouseY>=y&&mouseY<=y+h);
}

int main(int argc,char *argv[]){
    Graphics graphics;
    if(!graphics.init()){
        return -1;
    }
    SDL_Texture *background=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground1.jpeg");
    SDL_Texture *playButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.png");
    SDL_Texture *guideButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/guide.png");
    SDL_Texture*guideImage=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/backgroundGuide.jpeg");
    SDL_Texture*closeButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/close.png");
    SDL_Cursor *handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    
    bool running=true;
    bool showGuide=false;
    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT){
                running=false;
            }
            int mouseX=event.button.x;
            int mouseY=event.button.y;
            bool hovering=false;
            if(event.type==SDL_MOUSEBUTTONDOWN){
                
                if(mouseX>=410 && mouseX<=610&&mouseY>=530&&mouseY<=680){
                    SDL_SetCursor(handCursor);
                    cout<<"Start game"<<endl;
                }
                if(mouseX>=480&&mouseX<=540&&mouseY>=640&&mouseY<=700){
                    SDL_SetCursor(handCursor);
                    cout<<"Open guide"<<endl;
                    showGuide=true;
                }
                if(showGuide && mouseX>=870&&mouseX<=930&&mouseY>=90&&mouseY<=150){
                    SDL_SetCursor(handCursor);
                    cout<<"Close guide"<<endl;
                    showGuide=false;
                }
            }
            if(isMouseOver(mouseX, mouseY, 410, 530, 610, 680)||isMouseOver(mouseX, mouseY, 480, 640, 540, 700)||(showGuide&&isMouseOver(mouseX, mouseY, 870, 90, 930, 150))){
                SDL_SetCursor(handCursor);
                hovering = true;
            }
            if(!hovering){
                SDL_SetCursor(arrowCursor);
            }
        }
       
        
        graphics.clear();
        graphics.renderTexture(background, 0, 0, 1000, 900);
        graphics.renderTexture(playButton, 410, 530, 200, 150);
        graphics.renderTexture(guideButton, 480, 640, 60, 60);
        if (showGuide) {
            graphics.renderTexture(guideImage, 100, 120, 800, 650);
            graphics.renderTexture(closeButton, 870,90 , 60, 60);
            
        }

        graphics.present();
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(guideButton);
    SDL_DestroyTexture(closeButton);
    return 0;
}
