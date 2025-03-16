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
#include "constants.h"
using namespace std;
const int colorR=120;
const int colorG=255;
const int colorB=255;
const int colorAlpha=255;
const int timeBarX=300;
const int timeBarY=100;
const int timeBarWidth=600;
const int timeBarHeight=30;
const int timeBarTotalTime=420000;
const int closeButtonX=1020;
const int closeButtonY=70;
const int closeButtonWidth=60;
const int closeButtonHeight=60;
const int playButtonX=510;
const int playButtonY=540;
const int playButtonWidthReal=210;
const int playButtonHeightReal=110;
const int playButtonWidth=220;
const int playButtonHeight=170;
const int playImageX=0;
const int playImageY=0;
const int timeIconX=240;
const int timeIconY=95;
const int timeIconWidth=40;
const int timeIconHeight=40;
const int volumeX=1100;
const int volumeY=20;
const int volumeWidth=70;
const int volumeheight=70;
const int scoreX=30;
const int scoreY=30;
const int guideButtonX=580;
const int guideButtonY=660;
const int guideButtonWidth=75;
const int guideButtonHeight=75;
const int guideButton2X=930;
const int guideButton2Y=700;
const int guideButton2Width=70;
const int guideButton2Height=70;
const int homeIconX=200;
const int homeIconY=700;
const int homeIconWidth=70;
const int homeIconHeight=70;
const int delay=500;
const int replayX=480;
const int replayY=550;
const int replayWidthReal=220;
const int replayHeightReal=160;
const int replayWidth=250;
const int replayHeight=250;
const int winInfoX=150;
const int winInfoY=100;
const int winInfoWidth=900;
const int winInfoHeight=750;
const int numberScore=10;
const int SCREEN_WIDTH=1200;
const int SCREEN_HEIGHT=950;
const int ROW=4,COL=4;
const int ICON_SIZE=65;
const int numberIconPokemon=36;
const int musicButtonX=1000;
const int musicButtonY=20;
const int musicButtonWidth=70;
const int musicButtonHeight=70;
const int delayMusic=50;

bool isMouseOver(int mouseX,int mouseY,int x,int y,int w,int h){
    return (mouseX>=x&&mouseX<=x+w&&mouseY>=y&&mouseY<=y+h);
}
Graphics graphics;
SDL_Texture *background, *playButton, *guideButton, *guideImage, *closeButton;
SDL_Texture *playImage, *timeIcon, *volumeOn, *volumeOff, *winInfo, *loseInfo,*musicOn,*musicOff;
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
    musicOn=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/musicOn.png");
    musicOff=graphics.loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/musicOff.png");
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
    SDL_Color colorTimeBar={colorR,colorG,colorB,colorAlpha};
    TimeBar timeBar(timeBarX,timeBarY,timeBarWidth,timeBarHeight,timeBarTotalTime,colorTimeBar);
    Score _score(renderer);
    Controller _board(ROW,COL);
    ButtonEvent buttonEvent(renderer,ROW,COL,&_score,&_board);
    
    loadTextures();
    SDL_Cursor *handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    
    
    bool running=true;
    bool showGuide=false;
    bool isPlaying=false;
    bool volume=false;
    bool hasPlayedSound = false;
    bool playMusicSound=false;
    
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

                        if (mouseX >= closeButtonX && mouseX <= (closeButtonX+closeButtonWidth) && mouseY >= closeButtonY && mouseY <= (closeButtonY+closeButtonHeight)) {
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

                if(mouseX>=playButtonX && mouseX<=(playButtonX+playButtonWidthReal)&&mouseY>=playButtonY&&mouseY<=(playButtonY+playButtonHeightReal)&&!isPlaying){
                    SDL_SetCursor(handCursor);
                    cout<<"Start game"<<endl;
                    isPlaying=true;
                   playMusicSound=true;
                   SoundManager::GetInstance().PlayMusicGameSound();
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
                        graphics.renderTexture(playImage, playImageX, playImageY, SCREEN_WIDTH,SCREEN_HEIGHT);
                        graphics.renderTexture(timeIcon, timeIconX, timeIconY, timeIconWidth, timeIconHeight);
                        
                        if(!volume){
                            graphics.renderTexture(volumeOn, volumeX, volumeY, volumeWidth, volumeheight);
                        }else{
                            graphics.renderTexture(volumeOff, volumeX, volumeY, volumeWidth, volumeheight);
                        }

                        _score.render(scoreX, scoreY);
                        timeBar.render(renderer);
                        buttonEvent.renderBoard();
                        graphics.present();
                }
                if(isPlaying){
                    buttonEvent.handleEvent(event);
                }
                if(mouseX>=guideButtonX&&mouseX<=(guideButtonX+guideButtonWidth)&&mouseY>=guideButtonY&&mouseY<=(guideButtonY+guideButtonHeight)&&!isPlaying){
                    SDL_SetCursor(handCursor);
                    cout<<"Open guide"<<endl;
                    showGuide=true;
                }
                if (isPlaying &&
                    ((mouseX >= guideButton2X && mouseX <= (guideButton2X+guideButton2Width) && mouseY >= guideButton2Y && mouseY <= (guideButton2Y+guideButton2Height) && timeBar.isTimeUp()) ||
                     (mouseX >= guideButton2X && mouseX <= (guideButton2X+guideButton2Width) && mouseY >= guideButton2Y && mouseY <= (guideButton2Y+guideButton2Height) && _score.getScore() >= (ROW*COL*10)/2
                    ))) {
                    SDL_SetCursor(handCursor);
                    cout << "Open guide 2" << endl;
                    showGuide = true;
                    
                }
                if (isPlaying &&
                    ((mouseX >= homeIconX && mouseX <= (homeIconX+homeIconWidth) && mouseY >= homeIconY && mouseY <= (homeIconY+homeIconHeight) && timeBar.isTimeUp()) ||
                     (mouseX >= homeIconX  && mouseX <= (homeIconX+homeIconWidth)&& mouseY >= homeIconY && mouseY <=(homeIconY+homeIconHeight)&& _score.getScore() >= (ROW*COL*10)/2))) {
                    SDL_SetCursor(handCursor);
                    cout<<"Go home"<<endl;
                    Mix_HaltMusic();
                    Mix_HaltChannel(-1);
                    isPlaying = false;
                       showGuide = false;
                       hasPlayedSound = false;
                       _score.resetScore();
                    _score.updateTexture();
                       _board.reset();
                       timeBar.isTimeUp();
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                       graphics.clear();
                       graphics.renderTexture(background, playImageX, playImageY, SCREEN_WIDTH,SCREEN_HEIGHT);
                       graphics.renderTexture(playButton, playButtonX, playButtonY, playButtonWidth, playButtonHeight);
                       graphics.renderTexture(guideButton, guideButtonX, guideButtonY, guideButtonWidth, guideButtonHeight);
                       graphics.present();
                }
                

                if(mouseX>=replayX&&mouseX<=(replayX+replayWidthReal)&&mouseY>=replayY&&mouseY<=(replayY+replayHeightReal) && (timeBar.isTimeUp() || _score.getScore() >= (ROW*COL*10)/2) && !showGuide){
                    SDL_SetCursor(handCursor);
                    cout<<"Replay game"<<endl;
                    Mix_HaltMusic();
                       Mix_HaltChannel(-1);
                       SDL_Delay(delayMusic);
                    isPlaying=true;
                    timeBar.start();
                    _score.resetScore();
                    _score.updateTexture();
                    hasPlayedSound=false;
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                    _board.reset();
                        cout << "Matrix after reset:" << endl;
                        _board.showMatrix();
                    SoundManager::GetInstance().PlayMusicGameSound();
                        graphics.clear();
                        graphics.renderTexture(playImage, playImageX, playImageY,SCREEN_WIDTH,SCREEN_HEIGHT);
                        graphics.renderTexture(timeIcon,timeIconX, timeIconY, timeIconWidth, timeIconHeight);
                        
                        if(!volume){
                            graphics.renderTexture(volumeOn, volumeX, volumeY, volumeWidth, volumeheight);
                        }else{
                            graphics.renderTexture(volumeOff, volumeX, volumeY, volumeWidth, volumeheight);
                        }

                        _score.render(scoreX, scoreY);
                        timeBar.render(renderer);
                        buttonEvent.renderBoard();
                        
                        graphics.present();
                    
                }
                
                if(mouseX>=musicButtonX&&mouseX<=(musicButtonX+musicButtonWidth)&&mouseY>=musicButtonY&&mouseY<=(musicButtonY+musicButtonHeight)){
                    playMusicSound=!playMusicSound;
                    if(!playMusicSound){
                        Mix_HaltMusic();
                        Mix_HaltChannel(-1);
                    }else{
                        Mix_HaltMusic();
                           Mix_HaltChannel(-1);
                           SDL_Delay(delayMusic);
                        SoundManager::GetInstance().PlayMusicGameSound();
                    }
                }
                
                if(mouseX >= volumeX && mouseX <= (volumeX+volumeWidth) && mouseY >= volumeY && mouseY <= (volumeY+volumeheight)) {
                    volume = !volume;

                    if (volume) {
                        Mix_VolumeChunk(clickSound, 0);
                        Mix_VolumeChunk(SoundManager::GetInstance().soundLinked, 0);
                        Mix_VolumeChunk(SoundManager::GetInstance().soundOho, 0);
                        
                    } else {
                        Mix_VolumeChunk(clickSound, MIX_MAX_VOLUME);
                        Mix_VolumeChunk(SoundManager::GetInstance().soundLinked, MIX_MAX_VOLUME);
                        Mix_VolumeChunk(SoundManager::GetInstance().soundOho, MIX_MAX_VOLUME);
                    }
                }
                
                    if (isMouseOver(mouseX, mouseY, playButtonX, playButtonY, playButtonWidth, playButtonHeight) ||  // Play button
                        isMouseOver(mouseX, mouseY,guideButtonX, guideButtonY, guideButtonWidth, guideButtonHeight) ||   // Guide button
                        isMouseOver(mouseX, mouseY, closeButtonX, closeButtonY, closeButtonWidth, closeButtonHeight) ||   // Close guide button
                        isMouseOver(mouseX, mouseY, volumeX, volumeY, volumeWidth, volumeheight))  // Volume button
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
                if(isMouseOver(mouseX, mouseY, playButtonX, playButtonY, playButtonWidth, playButtonHeight)||isMouseOver(mouseX, mouseY,guideButtonX, guideButtonY, guideButtonWidth, guideButtonHeight)||isMouseOver(mouseX, mouseY, volumeX, volumeY, volumeWidth, volumeheight)||isMouseOver(mouseX, mouseY, guideButton2X, guideButton2Y, guideButton2Width, guideButton2Height)||isMouseOver(mouseX, mouseY, homeIconX, homeIconY, homeIconWidth, homeIconHeight)||isMouseOver(mouseX, mouseY, musicButtonX, musicButtonY, musicButtonWidth, musicButtonHeight)){
                    SDL_SetCursor(handCursor);
                    hovering = true;
                }
                if(!hovering){
                    SDL_SetCursor(arrowCursor);
                }
            }
            
           
            graphics.clear();
            graphics.renderTexture(background, playImageX, playImageY, SCREEN_WIDTH,SCREEN_HEIGHT);
            graphics.renderTexture(playButton, playButtonX, playButtonY, playButtonWidth, playButtonHeight);
            graphics.renderTexture(guideButton, guideButtonX, guideButtonY, guideButtonWidth, guideButtonHeight);
    
            if(isPlaying){
                
                graphics.renderTexture(playImage,  playImageX, playImageY, SCREEN_WIDTH,SCREEN_HEIGHT);
                graphics.renderTexture(timeIcon, timeIconX, timeIconY, timeIconWidth, timeIconHeight);
                if(!volume){
                    graphics.renderTexture(volumeOn, volumeX, volumeY, volumeWidth, volumeheight);
                }else{
                    graphics.renderTexture(volumeOff, volumeX, volumeY, volumeWidth, volumeheight);
                }
                if(playMusicSound){
                    graphics.renderTexture(musicOn, musicButtonX, musicButtonY, musicButtonWidth, musicButtonHeight);
                }else{
                    graphics.renderTexture(musicOff, musicButtonX, musicButtonY, musicButtonWidth, musicButtonHeight);
                }
               
               
                _score.render(scoreX, scoreY);
                if(_score.getScore()>=(ROW*COL*10)/2){
                    graphics.renderTexture(winInfo, winInfoX, winInfoY, winInfoWidth, winInfoHeight);
                    graphics.renderTexture(homeIcon,homeIconX, homeIconY, homeIconWidth, homeIconHeight);
                    graphics.renderTexture(replay, replayX, replayY, replayWidth, replayHeight);
                    graphics.renderTexture(guideButton2, guideButton2X, guideButton2Y, guideButton2Width, guideButton2Height);
                    
                    if (!hasPlayedSound) {
                           SoundManager::GetInstance().PlayWinSound();
                           hasPlayedSound = true;
                        SDL_Delay(delay);
                       }
                    Mix_Volume(-1, 0);
                    
                }else if(timeBar.isTimeUp()){
                    graphics.renderTexture(loseInfo, winInfoX, winInfoY, winInfoWidth, winInfoHeight);
                    graphics.renderTexture(homeIcon, homeIconX, homeIconY, homeIconWidth, homeIconHeight);
                    graphics.renderTexture(replay,replayX, replayY, replayWidth, replayHeight);
                    graphics.renderTexture(guideButton2, guideButton2X, guideButton2Y, guideButton2Width, guideButton2Height);
                    
                    if (!hasPlayedSound) {
                           SoundManager::GetInstance().PlayLoseSound();
                           hasPlayedSound = true;
                        SDL_Delay(delay);
                       }
                    Mix_Volume(-1, 0);
                }else{
                    timeBar.render(renderer);
                    buttonEvent.renderBoard();
                }
            }
        if (showGuide) {
            graphics.renderTexture(guideImage, winInfoX, winInfoY, winInfoWidth, winInfoHeight);
            graphics.renderTexture(closeButton, closeButtonX,closeButtonY, closeButtonWidth, closeButtonHeight);
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
