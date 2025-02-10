#include <iostream>
#include <SDL2/SDL.h>
#include<SDL_image.h>



using namespace std;

int main(){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        printf("Error:%s\n",SDL_GetError());
        return 1;
    }
    SDL_Window *window=SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Error:%s\n",SDL_GetError());
        return 1;
    }
    SDL_Event event;
    bool quit=false;
    while(!quit){
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT){
                quit=true;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
