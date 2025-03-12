#include <windows.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Tetris.h"
#include "consoleUTILS.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define ESC 27

using namespace std;

vector<int> readdata() {
    ifstream file("userdata.txt");
    if (file.is_open()) {
        vector<int> data(3, 0);
        for (int i = 0; i < 3; i++) file >> data[i];
        file.close();
        return data;
    } else {
        ofstream file("userdata.txt", ios::out | ios::trunc);
        file<<25<<endl<<25<<endl<<0<<endl;
        file.close();
        return readdata();
    }
}

vector<int> data = readdata();
int WIDTH =(data[0] > 2) ? data[0] : 50;
int HEIGHT =(data[1] > 2) ? data[1] : 25;
vector<vector<int>> map(HEIGHT, vector<int>(WIDTH, 0));

void input(Tetris& t1, Game& game){
    if (_kbhit()){
        int ch =_getch();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));// from stackoverflow
        if(ch ==SPACE) t1.hardDrop();
        if(ch ==ESC) game.Pause();
        if(ch ==101 && game.isDev_mode()){
            system("cls");
            game.DeveloperMode();
        }

        if(ch == 224) {
            ch = _getch();
            switch (ch){
                case KEY_UP: t1.Rotate(); break;
                case KEY_DOWN: t1.moveDown(); break;
                case KEY_LEFT: t1.moveLeft(); break;
                case KEY_RIGHT: t1.moveRight(); break;
            }
        }
    }
}


int main(){
    srand(time(0));
    Tetris t1;
    Game game(t1, data[2]);

    HWND s = GetConsoleWindow(); //from stackoverflow
    MoveWindow(s, 300, 100, 480, 620, true);
    hideCursor();
    system("cls");

    t1.createNewTetromino();
    t1.RenderTetris();
    game.Startmenu();


    while (true) {
        while (!game.isgameOver()) {

            if(game.isDev_mode()){
                gotoxy(WIDTH*2 + 5, 6);
                setColor(6);
                cout<< "DEVELOPER MODE: ON";
                gotoxy(WIDTH*2 + 5, 7);
                cout<<"PRESS E to swtich to dev-menu";
                setColor(7);

            }

            data= readdata();
            gotoxy(WIDTH/2 - 5, 1);
            cout << "SCORE: " << game.Score();
            gotoxy(WIDTH/2 + 10, 1);
            cout << "HIGHEST: " << data[2];
            game.update();

            if(game.Score() > data[2]) game.writedata(WIDTH, HEIGHT, game.Score());

            input(t1, game);
        }
        if (game.GameoverScreen() == 1) game.Reset();
    }
    system("cls");
    return 0;
}