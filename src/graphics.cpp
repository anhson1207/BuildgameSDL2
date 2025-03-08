
#include "graphics.hpp"
#include <iostream>
using namespace std;
Graphics::Graphics() : window(nullptr),renderer(nullptr){}

Graphics::~Graphics(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
bool Graphics::init(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0){
        cout<<"SDL error"<<SDL_GetError()<<endl;
        return false;
    }
    window=SDL_CreateWindow("Pikachu Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 950, SDL_WINDOW_SHOWN);
    if(!window){
        cout<<"Can't open the window,error"<<SDL_GetError()<<endl;
        return false;
    }
    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        cout<<"Can't make renderer,error"<<SDL_GetError()<<endl;
        return false;
    }
    
    //khoi tao image
    if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)){
        cout<<"Can't initialization SDL_image,error"<<IMG_GetError()<<endl;
        return false;
        
    }
    return true;
}
SDL_Texture *Graphics::loadTexture(const string &filePath){
    SDL_Texture *texture =IMG_LoadTexture(renderer, filePath.c_str());
    if(!texture){
        cout<<"Can't load image"<<filePath<<"| Error:"<<IMG_GetError()<<endl;
    }
    return texture;
}
void Graphics::renderTexture(SDL_Texture *texture, int x, int y,int w,int h){
    SDL_Rect dst={x,y,w,h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}
void Graphics::clear(){
    SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
    SDL_RenderClear(renderer);
}
void Graphics::present(){
    SDL_RenderPresent(renderer);
}
SDL_Renderer *Graphics::getRenderer(){
    return renderer;
}
