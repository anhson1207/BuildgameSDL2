#ifndef board_hpp
#define board_hpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Score.hpp"
using namespace std;

 const int ROW=10,COL=12;
 const int ICON_SIZE=65;

struct Point{
    int x,y;
    Point(int _x,int _y): x(_x),y(_y){}
};
class Controller{
private:
    int row,col;
    
public:
    vector<vector<int>>matrix;
    Controller(int _row,int _col);
    void showMatrix();
    void createMatrix();
    
    int getRow(){
        return row;
    }
    int getCol(){
        return col;
    }
    vector<vector<int>>getMatrix(){
        return matrix;
    }
    void setRow(int _row){
        row=_row;
    }
    void setCol(int _col){
        col=_col;
    }
    void setMatrix(const vector<vector<int>>&_matrix){
        matrix=_matrix;
    }
    bool canConnect(int x1, int y1, int x2, int y2);
    void removePair(int x1, int y1, int x2, int y2);
    vector<pair<int, int>>findPath(int x1, int y1, int x2, int y2);
    bool selectPokemon(int x1,int y1,int x2,int y2);
    void reset();
};

class ButtonEvent{
private:
    Score *score;
    SDL_Renderer *renderer;
    SDL_Texture *icon[36];
    Controller controller;
    
    SDL_Texture *playButton;
    SDL_Rect playButtonRect;
    Controller* board;
public:
    bool showBoard=false;
    ButtonEvent(SDL_Renderer *ren,int row,int col,Score* _score,Controller* _board);
    void handleClick(int x, int y);
    void handleEvent(SDL_Event &event){
        if(event.type==SDL_MOUSEBUTTONDOWN){
        
            int x=event.button.x;
            int y=event.button.y;
            if (!showBoard && x >= playButtonRect.x && x <= playButtonRect.x + playButtonRect.w &&
            y >= playButtonRect.y && y <= playButtonRect.y + playButtonRect.h) {
                            showBoard = true;
        }
            int mouseX=event.button.x;
           int mouseY=event.button.y;
            int boardX = (1200 - (COL * ICON_SIZE)) / 2;
            int boardY = (950 - (ROW * ICON_SIZE)) / 2;
         
           if (mouseX >= boardX && mouseX <= boardX + COL * ICON_SIZE &&
             mouseY >= boardY && mouseY <= boardY + ROW * ICON_SIZE) {
            
                int x = (mouseY - boardY) / ICON_SIZE;
                int y = (mouseX - boardX) / ICON_SIZE;
                handleClick(x, y);
                renderBoard();
            }
            }
        }
    void loadIcon();
    SDL_Texture *loadTexture(const string &path);
    void renderBoard();
    bool isMouseOver(int mouseX, int mouseY, int x, int y, int w, int h);
    bool isPokemonClicked(int mouseX,int mouseY);
};

#endif /* board_hpp */
