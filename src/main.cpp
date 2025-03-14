#include "graphics.hpp"
#include "board.hpp"
#include "GameScene.hpp"
#include <SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "TimeBar.hpp"
#include "Score.hpp"
#include "SoundManager.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
using namespace std;
bool isMouseOver(int mouseX,int mouseY,int x,int y,int w,int h){
    return (mouseX>=x&&mouseX<=x+w&&mouseY>=y&&mouseY<=y+h);
}
Graphics graphics;
SDL_Texture *background, *playButton, *guideButton, *guideImage, *closeButton;
SDL_Texture *playImage, *timeIcon, *volumeOn, *volumeOff, *winInfo, *loseInfo;
SDL_Texture *homeIcon, *guideButton2, *replay;
Mix_Chunk* clickSound;



void loadTextures() {
    background = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground1.jpeg");
    playButton = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.png");
    guideButton = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/guide.png");
    guideImage = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/backgroudGuide.png");
    closeButton = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/close.png");
    playImage = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pokemonBackground2.jpeg");
    timeIcon = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/time.png");
    volumeOn = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/VolumeUp.png");
    volumeOff = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/VolumeMute.png");
    winInfo = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/win.jpeg");
    loseInfo = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/lose.jpeg");
    homeIcon = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/home.png");
    guideButton2 = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/bookGuide.png");
    replay = graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/replay.png");
}
int main(int argc,char *argv[]){
    if(!graphics.init()){
        return -1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }
    
    clickSound= Mix_LoadWAV("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/sounds/click.wav");
    if (clickSound == nullptr) {
        cout << "Failed to load click sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }
    SoundManager::GetInstance().LoadSounds();
   
    SDL_Renderer* renderer = graphics.getRenderer();
    SDL_Color colorTimeBar={120,255,255,255};
    TimeBar timeBar(300,100,600,30,420000,colorTimeBar);
    Score _score(renderer);
    Controller _board(10,12);
    ButtonEvent buttonEvent(renderer,ROW,COL,&_score,&_board);
    
    loadTextures();
    SDL_Cursor *handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    
    
    bool running=true;
    bool showGuide=false;
    bool isPlaying=false;
    bool volume=false;
    bool hasPlayedSound = false;
    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT){
                running=false;
            }
           
            if (showGuide) {
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;

                        if (mouseX >= 1020 && mouseX <= 1080 && mouseY >= 70 && mouseY <= 130) {
                            showGuide = false;
                            SDL_SetCursor(handCursor);
                            cout << "Close guide" << endl;
                        }
                    }
                    continue;
                }
            int mouseX=event.button.x;
            int mouseY=event.button.y;
            bool hovering=false;
            if(event.type==SDL_MOUSEBUTTONDOWN){

                if(mouseX>=510 && mouseX<=730&&mouseY>=540&&mouseY<=650&&!isPlaying){
                    SDL_SetCursor(handCursor);
                    cout<<"Start game"<<endl;
                    isPlaying=true;
                    timeBar.start();
                    _score.resetScore();
                    _score.updateTexture();
                    hasPlayedSound=false;
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                    _board.reset();
                    buttonEvent.showBoard = true;
                        cout << "Matrix after reset:" << endl;
                        _board.showMatrix();
                        graphics.clear();
                        graphics.renderTexture(playImage, 0, 0, 1200, 950);
                        graphics.renderTexture(timeIcon, 240, 95, 40, 40);
                        
                        if(!volume){
                            graphics.renderTexture(volumeOn, 1100, 20, 70, 70);
                        }else{
                            graphics.renderTexture(volumeOff, 1100, 20, 70, 70);
                        }

                        _score.render(30, 30);
                        timeBar.render(renderer);
                        buttonEvent.renderBoard();
                        graphics.present();
                }
                if(isPlaying){
                    buttonEvent.handleEvent(event);
                }
                if(mouseX>=580&&mouseX<=665&&mouseY>=660&&mouseY<=735&&!isPlaying){
                    SDL_SetCursor(handCursor);
                    cout<<"Open guide"<<endl;
                    showGuide=true;
                }
                if (isPlaying &&
                    ((mouseX >= 930 && mouseX <= 1000 && mouseY >= 700 && mouseY <= 770 && timeBar.isTimeUp()) ||
                     (mouseX >= 930 && mouseX <= 1000 && mouseY >= 700 && mouseY <= 770 && _score.getScore() >= 600))) {
                    SDL_SetCursor(handCursor);
                    cout << "Open guide 2" << endl;
                    showGuide = true;
                }
                if (isPlaying &&
                    ((mouseX >= 200 && mouseX <= 270 && mouseY >= 700 && mouseY <= 770 && timeBar.isTimeUp()) ||
                     (mouseX >= 200 && mouseX <= 270 && mouseY >= 700 && mouseY <= 770 && _score.getScore() >= 600))) {
                    SDL_SetCursor(handCursor);
                    cout<<"Go home"<<endl;
                    isPlaying = false;
                       showGuide = false;
                       hasPlayedSound = false;
                       _score.resetScore();
                    _score.updateTexture();
                       _board.reset();
                       timeBar.isTimeUp();
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                       graphics.clear();
                       graphics.renderTexture(background, 0, 0, 1200, 950);
                       graphics.renderTexture(playButton, 510, 540, 220, 170);
                       graphics.renderTexture(guideButton, 580, 660, 75, 75);
                       graphics.present();
                }
                

                if(mouseX>=480&&mouseX<=700&&mouseY>=550&&mouseY<=710&&timeBar.isTimeUp()&&!showGuide&&isPlaying){
                    SDL_SetCursor(handCursor);
                    cout<<"Replay game"<<endl;
                    isPlaying=true;
                    timeBar.start();
                    _score.resetScore();
                    _score.updateTexture();
                    hasPlayedSound=false;
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                    _board.reset();
                        cout << "Matrix after reset:" << endl;
                        _board.showMatrix();

                        graphics.clear();
                        graphics.renderTexture(playImage, 0, 0, 1200, 950);
                        graphics.renderTexture(timeIcon, 240, 95, 40, 40);
                        
                        if(!volume){
                            graphics.renderTexture(volumeOn, 1100, 20, 70, 70);
                        }else{
                            graphics.renderTexture(volumeOff, 1100, 20, 70, 70);
                        }

                        _score.render(30, 30);
                        timeBar.render(renderer);
                        buttonEvent.renderBoard();
                        
                        graphics.present();
                    
                }
                if(mouseX >= 1100 && mouseX <= 1170 && mouseY >= 20 && mouseY <= 90) {
                    volume = !volume;

                    if (volume) {
                        Mix_Volume(-1, 0);
                    } else {
                        Mix_Volume(-1, MIX_MAX_VOLUME);
                    }
                }
                
                    if (isMouseOver(mouseX, mouseY, 510, 540, 220, 170) ||  // Play button
                        isMouseOver(mouseX, mouseY, 580, 660, 75, 75) ||   // Guide button
                        isMouseOver(mouseX, mouseY, 1020, 70, 60, 60) ||   // Close guide button
                        isMouseOver(mouseX, mouseY, 1100, 20, 70, 70))  // Volume button
                    {
                        if(!volume){
                            Mix_PlayChannel(-1, clickSound, 0);
                        }
                        
                    }
                    
                    if (buttonEvent.isPokemonClicked(mouseX, mouseY)) {
                        if (isPlaying&&!volume) {
                            Mix_PlayChannel(-1, clickSound, 0);
                        }
                    }
                    
            }
                if(isMouseOver(mouseX, mouseY, 510, 540, 220, 170)||isMouseOver(mouseX, mouseY, 580, 660, 75, 75)||(showGuide&&isMouseOver(mouseX, mouseY, 870, 90, 930, 150))||isMouseOver(mouseX, mouseY, 1100, 20, 70, 70)||isMouseOver(mouseX, mouseY, 930, 700, 70, 70)||isMouseOver(mouseX, mouseY, 200, 700, 70, 70)){
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
    
            if(isPlaying){
                graphics.renderTexture(playImage, 0, 0, 1200, 950);
                graphics.renderTexture(timeIcon, 240, 95, 40, 40);
                if(!volume){
                    graphics.renderTexture(volumeOn, 1100, 20, 70, 70);
                }else{
                    graphics.renderTexture(volumeOff, 1100, 20, 70, 70);
                }
                _score.render(30, 30);
                if(_score.getScore()>=600){
                    graphics.renderTexture(winInfo, 150, 100, 900, 750);
                    graphics.renderTexture(homeIcon, 200, 700, 70, 70);
                    graphics.renderTexture(replay, 480, 550, 250, 250);
                    graphics.renderTexture(guideButton2, 930, 700, 70, 70);
                    
                    if (!hasPlayedSound) {
                           SoundManager::GetInstance().PlayWinSound();
                           hasPlayedSound = true;
                        SDL_Delay(500);
                       }
                    Mix_Volume(-1, 0);
                    
                }else if(timeBar.isTimeUp()){
                    graphics.renderTexture(loseInfo, 150, 100, 900, 750);
                    graphics.renderTexture(homeIcon, 200, 700, 70, 70);
                    graphics.renderTexture(replay, 480, 550, 250, 250);
                    graphics.renderTexture(guideButton2, 930, 700, 70, 70);
                    
                    if (!hasPlayedSound) {
                           SoundManager::GetInstance().PlayLoseSound();
                           hasPlayedSound = true;
                        SDL_Delay(500);
                       }
                    Mix_Volume(-1, 0);
                }else{
                    timeBar.render(renderer);
                    buttonEvent.renderBoard();
                }
            }
        if (showGuide) {
            graphics.renderTexture(guideImage, 150, 100, 900, 750);
            graphics.renderTexture(closeButton, 1020,70, 60, 60);
        }
        graphics.present();
        }
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(playButton);
        SDL_DestroyTexture(guideButton);
        SDL_DestroyTexture(closeButton);
        SoundManager::GetInstance().Cleanup();
        Mix_CloseAudio();
        return 0;
    }
