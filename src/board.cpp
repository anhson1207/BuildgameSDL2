#include <iostream>
#include "board.hpp"
#include "Score.hpp"
#include "SoundManager.hpp"
#include <random>
#include <cstring>
#include <queue>
#include <vector>
#include "constants.h"
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};


using namespace std;
struct Node {
    int x, y, dir, turns;
};

Controller::Controller(int _row, int _col) {
    row = _row;
    col = _col;
    cout << row << "," << col << endl;
    createMatrix();
    showMatrix();
}



void Controller::showMatrix() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Controller::createMatrix() {
    matrix.resize(row, vector<int>(col, 0));
    srand((unsigned int) time(0));
    int imgCount = numberIconPokemon;
    int max = 4;
    vector<int> arr(imgCount + 1, 0);
    vector<Point> listPoint;
    
    cout<<replayX<<" "<<replayY<<" ";
    
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            listPoint.push_back(Point(i, j));
        }
    }
    int i = 0;
    do {
        int index = rand() % imgCount + 1;
        if (arr[index] < max) {
            arr[index] += 2;
            for (int j = 0; j < 2; j++) {
               int size =(unsigned int) listPoint.size();
                if (size == 0) break;
                int pointIndex = rand() % size;
                matrix[listPoint[pointIndex].x][listPoint[pointIndex].y] = index;
                listPoint.erase(listPoint.begin() + pointIndex);
            }
            i++;
        }
    } while (i < row * col / 2);
}
void Controller::reset() {
    cout << "Reset Board!" << endl;
    matrix.clear();
    matrix.resize(row, vector<int>(col, 0));
    createMatrix();
    showMatrix();
}

ButtonEvent::ButtonEvent(SDL_Renderer *ren, int row, int col,Score *_score,Controller *_board) : renderer(ren) {
    board=_board;
    score=_score;
    showBoard = false;
    playButton = loadTexture("/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/0.png1");
    playButtonRect = {playButtonX,playButtonY,playButtonWidth,playButtonHeight};
    loadIcon();
}

void ButtonEvent::loadIcon() {
    for (int i = 1; i <= numberIconPokemon; i++) {
        string path = "/Users/nguyenanhson/Documents/BuildgameSDL2/assests/image/pikachu_image" + to_string(i) + ".png";
        icon[i] = loadTexture(path);
    }
}

SDL_Texture *ButtonEvent::loadTexture(const string &path) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        cout << "Failed to load image: " << path << " SDL_Error:" << SDL_GetError() << endl;
    }
    return texture;
}

void ButtonEvent::renderBoard() {

    auto matrix = board->getMatrix();
    int boardX = (SCREEN_WIDTH - (COL * ICON_SIZE)) / 2;
    int boardY = (SCREEN_HEIGHT - (ROW * ICON_SIZE)) / 2;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            int index = matrix[i][j];
                    if (index > 0) {
                SDL_Rect rect = {boardX + j * ICON_SIZE, boardY + i * ICON_SIZE, ICON_SIZE, ICON_SIZE};
                SDL_RenderCopy(renderer, icon[index], nullptr, &rect);
            }
        }
    }
}
vector<pair<int, int>> Controller::findPath(int x1,int y1,int x2,int y2){
    vector<vector<int>>e(ROW+2,vector<int>(COL+2,0));
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            e[i+1][j+1]=matrix[i][j]!=0;
        }
    }
    pair<int, int>s={x1+1,y1+1};
    pair<int, int>t={x2+1,y2+1};
    deque<pair<int, int>>q;
    vector<vector<pair<int, int>>>trace(e.size(),vector<pair<int, int>>(e[0].size(),{-1,-1}));
    q.push_back(t);
    trace[t.first][t.second]={-2,-2};
    e[s.first][s.second]=0;
    e[t.first][t.second]=0;
    while(!q.empty()){
        auto u=q.front();
        q.pop_front();
        if(u==s) break;
        for(int i=0;i<4;i++){
            int nx=u.first,ny=u.second;
            while(true){
                nx+=dx[i];
                ny+=dy[i];
                if(nx<0||nx>=e.size()||ny<0||ny>=e[0].size()||e[nx][ny]) break;
                if(trace[nx][ny].first==-1){
                    trace[nx][ny]=u;
                    q.push_back({nx,ny});
                }
            }
        }
    }
    vector<pair<int, int>>res;
    if(trace[s.first][s.second].first!=-1){
        while (s.first!=-2) {
            res.push_back({s.first-1,s.second-1});
            s=trace[s.first][s.second];
        }
    }
    return res;
}
bool Controller::canConnect(int x1, int y1, int x2, int y2){
    auto path=findPath(x1,y1,x2,y2);
    return path.size()>=2 &&path.size()<=4;
}
bool Controller::selectPokemon(int x1,int y1,int x2,int y2){
    if((x1==-1&&y1==-1)||(matrix[x1][y1]!=matrix[x2][y2])||(matrix[x1][y1]==0)||!canConnect(x1, y1, x2, y2)){
        return false;
    }
    return true;
}
void Controller::removePair(int x1, int y1, int x2, int y2) {
    matrix[x1][y1] = 0;
    matrix[x2][y2] = 0;
}


void ButtonEvent::handleClick(int x, int y) {
    if(!showBoard) return ;
    static int selectedX = -1, selectedY = -1;

    if (selectedX == -1 && selectedY == -1) {
        
        selectedX = x;
        selectedY = y;
    } else {
        if (selectedX == x && selectedY == y) {
           
            SoundManager::GetInstance().PlayOhoSound();
        } else {
            if (board->canConnect(selectedX, selectedY, x, y) &&
                board->selectPokemon(selectedX, selectedY, x, y)) {
               
                SoundManager::GetInstance().PlayLinkedSound();
                
                cout << "Matched: (" << selectedX << ", " << selectedY << ") -> (" << x << ", " << y << ")" << endl;
                board->removePair(selectedX, selectedY, x, y);

                if (score) {
                    score->addScore(numberScore);
                }
                renderBoard();
            } else {
                SoundManager::GetInstance().PlayOhoSound();
            }
        }
       
        selectedX = -1;
        selectedY = -1;
    }
}
bool ButtonEvent::isMouseOver(int mouseX, int mouseY, int x, int y, int w, int h) {
    return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}

bool ButtonEvent::isPokemonClicked(int mouseX, int mouseY){
    int boardX = (SCREEN_WIDTH - (COL * ICON_SIZE)) / 2;
    int boardY = (SCREEN_HEIGHT - (ROW * ICON_SIZE)) / 2;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(board->matrix[i][j]!=0){
                int x=boardX+j*ICON_SIZE;
                int y=boardY+i*ICON_SIZE;
                int w=ICON_SIZE;
                int h=ICON_SIZE;
                if(isMouseOver(mouseX, mouseY, x, y, w, h)){
                    return  true;
                }
            }
        }
    }
    return false;
}

