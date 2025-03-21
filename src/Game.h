#ifndef Game_H
#define Game_H

#include <vector>
#include "Tetris.h"

class Game {
private:
    Tetris& tetris;
    bool gameover;
    int score;
    int Difficulty=1;
    int highscore;
    bool dev=false; //Developer mode

public:
    Game(Tetris& tetris, int highestScore);
    void writedata(int width, int height, int highscore);
    void layout();
    void pauseMenu();
    void Pause();
    bool isgameOver();
    void update();
    void draw();
    bool checkGameover();
    void Reset();
    void clearLine();
    int GameoverScreen();
    void Startmenu();
    void Restart();
    void DeveloperMode();
    int Score();
    bool isDev_mode();
    void setDev_mode(bool val);

};

#endif