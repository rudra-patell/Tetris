#include "Game.h"
#include "consoleUTILS.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>

#define ESC 27
using namespace std;

extern int WIDTH, HEIGHT;
extern vector<vector<int>> map;

Game::Game(Tetris& tetris, int highestscore) : tetris(tetris), gameover(false) ,score(0), highscore(highestscore) {
    layout();
}

void Game::writedata(int width, int height, int highscore){
    ofstream file("userdata.txt",  std::ios::out | std::ios::trunc); //ios::trunc will always clear the file if it exists
    if(file.is_open()){
        file<<width<<endl;
        file<<height<<endl;
        file<<highscore<<endl;
        file.close();
    }
    else{
        cout<<"Unable to open file";
    }
}
void Game::layout(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0|| j == 0|| i ==HEIGHT-1|| j==WIDTH-1) map[i][j] =9;
            else if(map[i][j]>=10) continue;
            else map[i][j]=0;
        }
    }
}

void Game::pauseMenu(){
    gotoxy(WIDTH * 2 + 5, HEIGHT/2 -3);
    setColor(1);
    cout << "Game Paused"<<endl;
    gotoxy(WIDTH * 2 + 5, HEIGHT/2 -1);
    setColor(2);
    cout << "R - Resume"<<endl;
    gotoxy(WIDTH * 2 + 5, HEIGHT/2);
    cout << "E - Exit";
    gotoxy(WIDTH * 2 + 5, HEIGHT/2 + 1);
    cout << "M - Main menu";
    setColor(7);

PAUSE:
    char c = _getch();
    switch (c) {
        case 'r': 
            system("cls");
            draw();
            break;
        case 'e': 
            exit(0);
            break;
        case ESC: 
            system("cls"); 
            draw(); 
            break;
        case 'm':
            Startmenu();
            break; 
        default: 
            goto PAUSE;
    }
}

void Game::draw(){
    int startX =3, startY =4;

    gotoxy(startX, startY);

    for(int i = 0; i < HEIGHT; i++) {

        for(int j = 0; j < WIDTH; j++) {

            gotoxy(j*2 +startX,i +startY);

            if(map[i][j] == 1) {
                setColor(tetris.tetromino.color);
                cout << char(219)<<char(219);
                setColor(7);

            } else if(map[i][j] >=10) {
                setColor(map[i][j] -10);
                cout << char(219) <<char(219);
                setColor(7);

            } else if(map[i][j] ==0) cout<<"  ";
            else if(map[i][j] ==9) cout<<char(178)<<char(178);
        }
    }
}

bool Game::checkGameover(){
    for(int i = 0; i < WIDTH; i++) {
        if(map[2][i] >= 10) return true;
    }
    return tetris.spwancollision;
}

void Game::update(){
    tetris.moveDown();
    
    layout();
    tetris.RenderTetris();

    if(checkGameover()){
        gameover = true;
    }
    draw();
    clearLine();
    Sleep(250/Difficulty);
}

bool Game::isgameOver(){ return gameover; }

void Game::Pause(){ pauseMenu(); }

void Game::clearLine(){
    for(int i = HEIGHT- 2; i >0; i--) {
        bool full = true;
        for(int j =1;j <WIDTH - 1;j++) {
            if(map[i][j] == 0) { full = false; break; }
        }
        if(full) {
            for(int k = i;k >1;k--) {
                for(int j = 1; j <WIDTH -1;j++){
                    map[k][j] =map[k -1][j];
                }
            }
            for(int j =1; j< WIDTH -1; j++){
                map[1][j]= 0;
            }

            score +=WIDTH -2;

            i++;
            if(score > 5*(WIDTH -2)  && Difficulty <=5) Difficulty++;
            if(score > 15*(WIDTH -2) && Difficulty <=5) Difficulty++;
            if(score > 30*(WIDTH -2) && Difficulty <=5) Difficulty++;
            if(score > 50*(WIDTH -2) && Difficulty <=5) Difficulty++;//this will unlock the highest difficulty that is not available in start menu()
        }
    }
}

void Game::Reset(){
    gameover =false;
    score =0;
    map.assign(HEIGHT, vector<int>(WIDTH, 0));
    
    layout();

    tetris.spwancollision=false;
    tetris.createNewTetromino();
    tetris.RenderTetris();
}

int Game::GameoverScreen(){
    system("cls");
    gotoxy(WIDTH, HEIGHT/2 - 3);
    setColor(4);
    cout << "GAME OVER!!";
    gotoxy(WIDTH + 3, HEIGHT/2 - 1);
    setColor(2);
    cout << "Score: " << score << "        Highest Score: " << score;
    gotoxy(WIDTH + 1, HEIGHT/2 + 1);
    setColor(1);
    cout << "Press E - Exit";
    gotoxy(WIDTH + 1, HEIGHT/2 + 2);
    cout << "Press R - Restart the game";
    gotoxy(WIDTH + 1, HEIGHT/2 + 3);
    cout << "Press M - Main Screen";
    setColor(7);
    char in = _getch();
    switch (in) {
        case 'e': exit(0); break;
        case 'r': system("cls"); return 1;
        case 'm': Startmenu(); break;
    }
    return 0;
}

void Game::Startmenu(){
START:
    system("cls");
    gotoxy(10, 5);
    setColor(14);
    cout<<"Welcome to Tetris by Team Falcons";

    gotoxy(14, 7);
    setColor(1);
    cout<<"1. Start the Game";
    gotoxy(14, 9);
    cout<<"2. Options";
    gotoxy(14, 11);
    cout<<"3. Exit the Game";

    char in = _getch();
    switch (in) {
        case '1': system("cls"); break;

        case '2': system("cls");
            setColor(14);
            gotoxy(10, 5);
            cout<<"Options";
            setColor(1);
            gotoxy(14, 7);
            cout<<"1. Change Difficulty Level";
            gotoxy(14, 9);
            cout<<"2. Set Gridsize";
            gotoxy(14, 11);
            cout<<"3. Back to Main Menu";


            in=_getch();

            switch(in){
                case '1':
                    CHANGE_DIFFICULTY:

                    system("cls");
                    setColor(14);
                    gotoxy(10, 5);
                    cout<<"Change Difficulty Level";
                    setColor(3);
                    gotoxy(14, 7);
                    cout<<"1. Easy";
                    setColor(6);
                    gotoxy(14, 9);
                    cout<<"2. Normal";
                    setColor(4);
                    gotoxy(14, 11);
                    cout<<"3. Hard";
                    setColor(1);
                    gotoxy(14, 13);
                    cout<<"4. Back to Options";
                    setColor(7);

                    in=_getch();
                    switch(in){
                        case '1': Difficulty= 1; goto START; break;
                        case '2': Difficulty= 2; goto START; break;
                        case '3': Difficulty= 4; goto START; break;
                        case '4': system("cls"); break;
                        default:
                            gotoxy(14, 15);
                            setColor(4);
                            cout<<"Invalid Selection! Please try again.";
                            Sleep(1500);
                            system("cls");
                            setColor(7);
                            goto CHANGE_DIFFICULTY;
                    }
                    break;
                

                case '2': 
                    SETGRID:
                    system("cls");
                    setColor(14);
                    gotoxy(10, 5);
                    cout<<"Enter the Grid size ( (w,h) , limit (10, 10) - (60, 30)):";
                    int x, y;
                    gotoxy(16, 7);
                    setColor(1);
                    cin>>x>>y;
                    if(x>=10 && y>=10 && x<=60 && y<=30){
                        WIDTH = x; HEIGHT = y;

                        writedata(x, y , highscore);
                        setColor(7);

                        gotoxy(10, 10);

                        cout<<"Grid Size set Restarting the game....";

                        Restart();
                    }
                    else{
                        setColor(4);
                        cout<<"Invalid Grid size! Please try again.";
                        Sleep(1500);
                        goto SETGRID;

                    }
                    setColor(7);
                    break;

                case '3':
                    goto START;                 
                    break;
                
                default: 
                    gotoxy(14, 13);
                    setColor(4);
                    cout<<"Invalid Selection! Please try again.";
                    Sleep(1500);
                    system("cls");
                    goto START;

            }

        case '3': exit(0); break;

        default: 
            gotoxy(14, 13);
            setColor(4);
            cout<<"Invalid Selection! Please try again.";
            Sleep(1500);
            system("cls");
            goto START;
    }

}
void Game::Restart(){
    Sleep(2000);
    //Relaunch the program
    system("start tetris.exe"); 

    //exit the current window
    exit(0);
}


int Game::Score(){ return score; }

