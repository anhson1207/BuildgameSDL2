//
//  graphics.hpp
//  SDL2
//
//  Created by Nguyễn Anh Sơn on 10/02/2025.
//

#ifndef graphics_hpp
#define graphics_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;
class Graphics{
public:
    Graphics();
    ~Graphics();
    
    bool init();
    void clear();
    void present();
    SDL_Texture*loadTexture(const string &filePath);
    void renderTexture(SDL_Texture * texture,int x,int y,int w,int h);
    SDL_Renderer*getRenderer();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif /* graphics_hpp */
