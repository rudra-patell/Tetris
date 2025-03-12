#include "Tetris.h"
#include "consoleUTILS.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

extern int WIDTH, HEIGHT;
extern vector<vector<int>> map;

Tetris::Tetromino::Tetromino(char t, std::vector<std::vector<int>> s, int c)
    : type(t), shape(s), color(c) {}

Tetris::Tetris() : spwancollision(false), tetromino('I', {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}, 9) {
    tetrominoes = {
        {'I', {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}, 9},
        {'O', {{1,1}, {1,1}}, 14},
        {'T', {{0,1,0}, {1,1,1}, {0,0,0}}, 5},
        {'S', {{0,1,1}, {1,1,0}, {0,0,0}}, 12},
        {'Z', {{1,1,0}, {0,1,1}, {0,0,0}}, 10},
        {'J', {{1,0,0}, {1,1,1}, {0,0,0}}, 3},
        {'L', {{0,0,1}, {1,1,1}, {0,0,0}}, 15}
    };
}

void Tetris::Rotate(){
    int n = tetromino.shape.size();
    std::vector<std::vector<int>> rotated(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) rotated[j][n - 1 - i] = tetromino.shape[i][j];
    }
    tetromino.shape =rotated;
}

void Tetris::moveLeft(){
    if(x >= -1 && !isCollision(-1, 0)) x--;
}

void Tetris::moveRight(){
    if(x < WIDTH - int(tetromino.shape[0].size()) && !isCollision(1, 0)) x++;
}

void Tetris::moveDown(){
    if(!isCollision(0, 1)) y++;
    else{
        merge();
        createNewTetromino();
        RenderTetris();
    }
}

void Tetris::hardDrop(){
    while(!isCollision(0, 1)) y++;
    merge();
    createNewTetromino();
    RenderTetris();
}

bool Tetris::isCollision(int dx, int dy){
    for(int i = 0; i < int(tetromino.shape.size()); i++){
        for(int j = 0; j < int(tetromino.shape.size()); j++){
            if(tetromino.shape[i][j]) {
                int newX = x + j + dx;
                int newY = y + i + dy;
                if(newX <= 0|| newX >= WIDTH -1|| newY>=HEIGHT-1) return true;
                if(map[newY][newX] >= 10|| map[newY][newX] ==9) return true;
                if(map[newY][newX]==2|| newY <0) return true;
            }
        }
    }
    return false;
}

void Tetris::merge(){
    for(int i = 0; i < int(tetromino.shape.size()); i++){
        for(int j = 0; j < int(tetromino.shape[0].size()); j++){
            if(tetromino.shape[i][j]) map[y + i][x + j] = 10 + tetromino.color;
        }
    }
}

int Tetris::createNewTetromino(){
    tetromino = tetrominoes[rand() % tetrominoes.size()];
    x=WIDTH/2 -(int(tetromino.shape[0].size())/2);
    y=1;
    if(isCollision(0, 0)){
        spwancollision = true;
        setColor(4);
        gotoxy(WIDTH * 2 +5, HEIGHT/2 +3);
        cout<< "Spawn collision detected! Game over.";
        Sleep(1000);
        return -1;
    }
    RenderTetris();
    return 0;
}

void Tetris::RenderTetris(){
    for(int i = 0; i < int(tetromino.shape.size()); i++){
        for(int j = 0; j < int(tetromino.shape[0].size()); j++){
            if(tetromino.shape[i][j]) map[y + i][x + j] =1;
        }
    }
}

bool Tetris::currTetromino(){
    for(int i = 0; i < int(map.size()); i++){
        for(int j = 0; j < int(map[0].size()); j++){
            if(map[i][j] == 1) return true;
        }
    }
    return false;
}