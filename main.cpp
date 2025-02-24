#include <windows.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <fstream> //for file handling


#define KEY_UP 72  //defination for arrow keys
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77 
#define SPACE 32
#define ESC 27

void writedata(int width, int height, int highscore){
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


vector<int> readdata(){ //return the array of data [width, height, highscore]
    ifstream file("userdata.txt");
    if(file.is_open()){

        vector<int>data(3, 0);

        for(int i=0;i<3;i++){
            file>>data[i];
        }
        file.close();
        return data;
    }else{
        writedata(50, 25, 0); 
        file.close();
        return readdata(); //if file not found return default values
    }
}

//  basic required functions and global variables
vector<int> data=readdata();
int WIDTH = (data[0] > 2) ? data[0]: 50;
int HEIGHT = (data[1] > 2) ? data[1]: 25;
vector<vector<int>> map(HEIGHT, vector<int>(WIDTH, 0));//defining 2D vector grid

int difficulty=1;

void gotoxy(int x, int y){ //from stacksoverflow
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor(){
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
} 
void setColor(int color) { //color for console fonts(stack overflow)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


class Tetris{
    struct Tetromino {
        char type; // Type:'I', 'O', 'T', 'S', 'Z', 'J', 'L'
        std::vector<std::vector<int>> shape;// 2D shape matrix
        int x, y; // Position on the board

        Tetromino(char type,std::vector<std::vector<int>> shape) : type(t), shape(s), x(3), y(0) {}
    };

    Tetromino I('I', 
        {{1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}}
    );

    Tetromino O('O', 
        {{1,1},
        {1,1}}
    );

    Tetromino T('T', 
        {{0,1,0},
        {1,1,1},
        {0,0,0}}
    );

    Tetromino S('S', 
        {{0,1,1},
        {1,1,0},
        {0,0,0}}
    );

    Tetromino Z('Z', 
        {{1,1,0},
        {0,1,1},
        {0,0,0}}
    );

    Tetromino J('J', 
        {{1,0,0},
        {1,1,1},
        {0,0,0}}
    );

    Tetromino L('L', 
        {{0,0,1},
        {1,1,1},
        {0,0,0}}
    );

    std::vector<Tetromino> tetrominoes= {I, O, T, S, Z, J, L};


};







void input(){
    if(_kbhit()){
        int ch=int(_getch());

        switch (ch){
            case KEY_UP:
                Rotate();
                break;
            case KEY_DOWN:
                moveDown();
                break;
            case KEY_LEFT:
                moveLeft();
                break;
            case KEY_RIGHT:
                moveRight();
                break;
            case SPACE:
                hardDrop();
                break;
            case ESC:
                Pause();
        
        }
    }
}



