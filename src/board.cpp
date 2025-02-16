#include <iostream>
#include "board.hpp"
#include <random>
using namespace std;
Controller::Controller(int _row,int _col){
    row=_row;
    col=_col;
    cout<<row<<","<<col<<endl;
    createMatrix();
    showMatrix();
}
void Controller::showMatrix(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
void Controller::createMatrix(){
    matrix.resize(row, vector<int>(col,0));
    srand(time(0));
    int imgCount=36;
    int max=4;
    vector<int>arr(imgCount+1,0);
    vector<Point>listPoint;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            listPoint.push_back(Point(i, j));
        }
    }
    int i=0;
    do {
        int index=rand()%imgCount+1;
        if(arr[index]<max){
            arr[index]+=2;
            for(int j=0;j<2;j++){
                int size=listPoint.size();
                if(size==0) break;
                int pointIndex=rand()%size;
                matrix[listPoint[pointIndex].x][listPoint[pointIndex].y]=index;
                listPoint.erase(listPoint.begin()+pointIndex);
            }
            i++;
        }
    } while (i<row*col/2);
}
ButtonEvent::ButtonEvent (SDL_Renderer *ren,int row,int col) : renderer(ren), controller(row, col) {
    showBoard=false;
    playButton = loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/play.png1");
    playButtonRect = {510,540,220,110};
    loadIcon();
}
void ButtonEvent::loadIcon(){
    for(int i=1;i<=36;i++){
        string path="/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pikachu_image"+to_string(i)+".png";
        icon[i]=loadTexture(path);
    }
}
SDL_Texture *ButtonEvent::loadTexture(const string &path){
    SDL_Texture *texture=IMG_LoadTexture(renderer, path.c_str());
    if(!texture){
        cout<<"Failed to load image: "<<path<<" SDL_Error:"<<SDL_GetError()<<endl;
    }
    return texture;
    }
void ButtonEvent::renderBoard(){
    if(!showBoard){
        SDL_RenderCopy(renderer, playButton, nullptr, &playButtonRect);
        return ;
    }
    auto matrix=controller.getMatrix();
    int boardX=(1200-(COL*ICON_SIZE))/2;
    int boardY=(950-(ROW*ICON_SIZE))/2;
    
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            int index=matrix[i][j];
            if(index>0){
                SDL_Rect rect={boardX+j*ICON_SIZE,boardY+i*ICON_SIZE,ICON_SIZE,ICON_SIZE};
                SDL_RenderCopy(renderer, icon[index], nullptr, &rect);
            }
        }
    }
}
