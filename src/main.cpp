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
    public:

        int x, y;

        Tetris() :{
            createNewTetromino();
        }

        struct Tetromino {
            char type; // Type:'I', 'O', 'T', 'S', 'Z', 'J', 'L'
            std::vector<std::vector<int>> shape;// 2D shape matrix
            int x, y; // Position on the board
            char color; // Color

            Tetromino(char type,std::vector<std::vector<int>> shape) : type(t), shape(s), x(3), y(0) {}
        };

        Tetromino I('I', 
            {{1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}},
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


        void Rotate(Tetromino &t){ //rotate the shape by 90degrees
            int n= t.shape.size();
            std::vector<std::vector<int>> roteted(n, std::vector<int>(n, 0));

            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    roteted[j][n-1-i] = t.shape[i][j];
                }
            }
        }

        void moveLeft(){
            if(x>0 && !isCollision(-1, 0)) x--;
        }

        void moveRight(){
            if(x<WIDTH-int(tetromino.shape[0].size())) x++;
        }

        void moveDown(){
            if(!isCollision(0, 1)) y++;
        }

        void hardDrop{
            while(!isCollision(0, 1)){
                y++;
            }
            y--;
            createNewTetromino();
        }

        bool isCollision(int dx, int dy){
            for(int i=0; i<int(tetromino.shape.size()); i++){
                for(int j=0; j<int(tetromino.shape[0].size()); j++){
                    if(tetromino.shape[i][j] && 
                    (map[y+i+dy][x+j+dx] || y+i+dy>=HEIGHT || x+j+dx>= WIDTH || x+j+dx<=0)){
                        return true;
                    }
                }
            }
            return false;
        }

        // void merge(){
        //     for(int i=0; i<int(tetromino.shape.size()); i++){
        //         for(int j=0; j<int(tetromino.shape[0].size()); j++){
        //             if(tetromino.shape[i][j]){
        //                 map[y+i][x+j] = tetromino.type;
        //             }
        //         }
        //     }

        // }

        int createNewTetromino(){ //returns 0 if no spawn collision(gameover)
            tetromino = tetrominoes[rand() % tetrominoes.size()];
            x = WIDTH / 2 - int(tetromino.shape[0].size()) / 2;
            y = 0;

            RenderTetris();

            if(isCollision(0, 1)) return -1;
            return 0;
        }

        void RenderTetris(){
            for(int i=0; i<int(tetromino.shape.size()); i++){
                for(int j=0; j<int(tetromino.shape[0].size()); j++){
                    if(tetromino.shape[i][j]){
                        map[x+i][y+j] = 1;
                    }
                }
            }
        }


};


class Game{
    private:
        Tetris& tetris;
        bool gameover;
    public:
    Game(Tetris& tetris); { gameover = false; }
    void layout(vector<vector<int>> mp){
        for(int i=0; i<WIDTH; i++){
            for(int j=0; j<HEIGHT; j++){
                if(i==0 || j==0 || i==WIDTH-1 || j==HEIGHT-1) map[i][j]= 9; //border
            }
        }
    }

    void draw(){
        gotoxy(2,2);
        for(int i=0; i<WIDTH; i++){
            for(int j=0; j<HEIGHT; j++){
                if(map[i][j]==1){
                    gotoxy(i+2,j+2);
                    std::cout << char(219); //tetrimine
                }
                else if(map[i][j]==0){
                    gotoxy(i,j);
                    std::cout << " "; //empty space
                }
                else if(map[i][j]==9){
                    gotoxy(i+2,j+2);
                    std::cout << char(178); //border
                }
            }
        }
    }
    void update(){
        layout();
        int temp=tetris->creatNewTetris();
        draw();
        if(temp==-1) gameover=true;

    }
    bool isgameOver(){
        return gameover;
    }
    void pause(){}
    void resume(){}
    void start(){}
    void clearLine(){}

};




void input(){
    if(_kbhit()){
        int ch=int(_getch());

        switch (ch){
            case KEY_UP:
                Tetris.Rotate();
                break;
            case KEY_DOWN:
                Tetris.moveDown();
                break;
            case KEY_LEFT:
                Tetris.moveLeft();
                break;
            case KEY_RIGHT:
                Tetris.moveRight();
                break;
            case SPACE:
                Tetris.hardDrop();
                break;
            case ESC:
                Game.Pause();
        
        }
    }
}

int main(){
    srand(time(0));
    hideCursor();
    

    return 0;
}



