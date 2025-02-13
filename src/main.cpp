//
//  main.cpp
//  SDL2
//
//  Created by Nguyễn Anh Sơn on 10/02/2025.
//

#include "main.hpp"
#include "graphics.hpp"
#include <SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
int main(int argc,char *argv[]){
    Graphics graphics;
    if(!graphics.init()){
        return -1;
    }
    SDL_Texture *background=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground1.jpeg");
    SDL_Texture *playButton=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.jpeg");
    bool running=true;
    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT){
                running=false;
            }
            if(event.type==SDL_MOUSEBUTTONDOWN){
                int mouseX=event.button.x;
                int mouseY=event.button.y;
                if(mouseX>=300 && mouseX<=500&&mouseY>=300&&mouseY<=350){
                    cout<<"Start game"<<endl;
                }
            }
        }
        graphics.clear();
        graphics.renderTexture(background, 0, 0, 1000, 900);
        graphics.renderTexture(playButton, 410, 600, 200, 100);
        graphics.present();
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(playButton);
    return 0;
}
