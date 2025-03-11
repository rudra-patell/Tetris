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

using namespace std;

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
        writedata(25, 25, 0); 
        file.close();
        return readdata(); //if file not found return default values
    }
}

//  basic required functions and global variables
vector<int> data=readdata();
int WIDTH = (data[0] > 2) ? data[0]: 50;
int HEIGHT = (data[1] > 2) ? data[1]: 25;
vector<vector<int>> map(HEIGHT, vector<int>(WIDTH, 0));//defining 2D vector grid


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
        struct Tetromino { 
            char type; // Type:'I', 'O', 'T', 'S', 'Z', 'J', 'L'
            std::vector<std::vector<int>> shape;// 2D shape matrix
            int color; // 0 to 15 for more info goto cmd and type color -h
        
            // char color; // Color
        
            Tetromino(char t ,std::vector<std::vector<int>> s, int c) : type(t), shape(s), color(c) {}
        };
        
        int x, y;
        bool spwancollision;
        std::vector<Tetromino> tetrominoes;

        // Tetromino I('I', 
        //     {{1,1,1,1},
        //      {0,0,0,0},
        //      {0,0,0,0},
        //      {0,0,0,0}});

        // Tetromino O('O', 
        //     {{1,1},
        //      {1,1}});

        // Tetromino T('T', 
        //     {{0,1,0},
        //      {1,1,1},
        //      {0,0,0}});

        // Tetromino S('S', 
        //     {{0,1,1},
        //      {1,1,0},
        //      {0,0,0}});

        // Tetromino Z('Z', 
        //     {{1,1,0},
        //      {0,1,1},
        //      {0,0,0}});

        // Tetromino J('J', 
        //     {{1,0,0},
        //      {1,1,1},
        //      {0,0,0}});

        // Tetromino L('L', 
        //     {{0,0,1},
        //      {1,1,1},
        //      {0,0,0}});

        Tetris() : spwancollision(false),  tetromino('I', {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}, 9){
                tetrominoes = {
                    {'I', {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}, 9},
                    {'O', {{1,1}, {1,1}}, 14},
                    {'T', {{0,1,0}, {1,1,1}, {0,0,0}}, 5},
                    {'S', {{0,1,1}, {1,1,0}, {0,0,0}}, 12},
                    {'Z', {{1,1,0}, {0,1,1}, {0,0,0}}, 10},
                    {'J', {{1,0,0}, {1,1,1}, {0,0,0}}, 3} ,
                    {'L', {{0,0,1}, {1,1,1}, {0,0,0}}, 15}
                };
                createNewTetromino();
            }
        
        Tetromino tetromino = tetrominoes[rand() % tetrominoes.size()]; //creating a random tetromino

        void Rotate(){ //rotate the shape by 90degrees
            int n= tetromino.shape.size();
            std::vector<std::vector<int>> roteted(n, std::vector<int>(n, 0));

            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    roteted[j][n-1-i] = tetromino.shape[i][j];
                }
            }

            tetromino.shape = roteted;
        }
        void moveLeft(){
            if(x >= -1 && !isCollision(-1, 0)){ //don't know why it works, but don't touch it
                x--;
            }
        }
        void moveRight(){
            if(x<WIDTH-int(tetromino.shape[0].size()) && !isCollision(1, 0)){
                x++;  
            } 
        }
        void moveDown(){
            if(!isCollision(0, 1)) {
                y++;
            } else {
                merge();
                createNewTetromino();
                RenderTetris();
            }
        }
        void hardDrop(){
            while(!isCollision(0, 1)){
                y++;
            }
            merge();
            createNewTetromino();
            RenderTetris();

        }
        bool isCollision(int dx, int dy){
            for(int i=0; i<int(tetromino.shape.size()); i++){
                for(int j=0; j< int(tetromino.shape.size()); j++){

                    if(tetromino.shape[i][j]){
                        int newX= x + j+ dx;
                        int newY= y + i + dy;

                        //boundries
                        if(newX<=0 || newX>=WIDTH-1 || newY>= HEIGHT-1) {
                            return true;
                        }
                        //existing block
                        if(map[newY][newX] >=10 || map[newY][newX]==9){
                            return true;
                        }
                        //for spwan collition
                        if(map[newY][newX] ==2||newY<0) { 
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        void merge(){
            for(int i=0; i<int(tetromino.shape.size()); i++){
                for(int j=0; j<int(tetromino.shape[0].size()); j++){
                    if(tetromino.shape[i][j]){ 
                        map[y+i][x+j] = 10 + tetromino.color; //Mark the fallen tetromino as part of the grid adding 10 for storing color
                    }
                }
            }
        }
        int createNewTetromino(){ //returns 0 if no spawn collision(gameover)

            tetromino = tetrominoes[rand() % tetrominoes.size()]; //comment out to turn off randominzation
            x = WIDTH / 2 - (int(tetromino.shape[0].size()) / 2);
            y = 1;

           
            if (isCollision(0, 0)) {
                spwancollision=true;

                setColor(4);
                gotoxy(WIDTH*2 +5 , HEIGHT/2 +3);
                cout << "Spawn collision detected! Game over.";
                Sleep(1000);
                
                return -1; // Game over
            }
            RenderTetris();
            

            return 0;
        }
        void RenderTetris(){
            for(int i=0; i<int(tetromino.shape.size()); i++){
                for(int j=0; j<int(tetromino.shape[0].size()); j++){
                    if(tetromino.shape[i][j]){
                        map[y+ i][x + j] = 1;
                    }
                }
            }
        }
        bool currTetromino(vector<vector<int>> mp){
            for(int i=0; i< int(mp.size()); i++){
                for(int j=0; j<int(mp[0].size()); j++){
                    if(mp[i][j] ==1){
                        return true;
                    }

                }
            }
            return false;
        }

};


class Game{
    private:
        Tetris& tetris;
        bool gameover;
        int score;
    public:
    Game(Tetris& tetris): tetris(tetris), gameover(false) {}
    
    void layout(std::vector<std::vector<int>>& mp){
        // cout<<"layout"<<endl;
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                if(i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1){
                    mp[i][j]= 9; //border
                    // cout<<mp[i][j];
                    }
                else if(mp[i][j]>= 10){
                    continue;
                    // cout<<mp[i][j];e
                }
                else{
                    mp[i][j]=0;
                }
        }

    } 

}

    void pauseMenu(){
        gotoxy(WIDTH*2 + 5, HEIGHT/2 - 3 );
        setColor(1);
        std::cout<<"Game Paused"<<std::endl;
        gotoxy(WIDTH*2 + 5, HEIGHT/2 - 1 );
        setColor(2);
        std::cout<<"R - Resume"<<endl;
        gotoxy(WIDTH*2 + 5, HEIGHT/2 );
        cout<<"E - Exit";

        setColor(7);

        PAUSE:

        char c=_getch();

        switch(c){
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

            default:
                goto PAUSE;

        }

    }

    void draw(){

        int startX=3 , startY=4;
        
        gotoxy(startX, startY);
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                gotoxy(j*2 +startX, i + startY);
                if(map[i][j]== 1){
                    setColor(tetris.tetromino.color);
                    std::cout << char(219); //tetrimine char(219)
                    std::cout << char(219);
                    setColor(7);
                }
                if(map[i][j]>= 10){
                    setColor(map[i][j] - 10); //get color
                    std::cout << char(219); //tetrimine char(219)
                    std::cout << char(219);
                    setColor(7);
                }
                else if(map[i][j]==0){
                    std::cout << "  "; //empty space
                }
                else if(map[i][j]==9){
                    std::cout << char(178); //border
                    std::cout << char(178);
                }
            }
        }
    }

    bool checkGameover() {
        for(int i=0;i <WIDTH;i++) {
            if(map[2][i] >=10) { // If any block in row 2 is occupied
                return true;
            }
        }
        return tetris.spwancollision;
    }

    void update(){

        tetris.moveDown();
        tetris.merge();
        layout(map);
        tetris.RenderTetris();
        if(checkGameover()) {
            Sleep(2000);
            gameover=true;
            
        }
        draw();
        clearLine();
        Sleep(250);
        

    }

    bool isgameOver(){
        return gameover;
    }

    void Pause(){
        pauseMenu();
    }

    void clearLine() {
        for (int i =HEIGHT -2;i >0;i--) { // Start from bottom to top
            bool full = true;    
            // Check if row is full
            for (int j = 1; j <WIDTH-1; j++) {
                if (map[i][j] == 0) {
                    full = false;
                    break;
                }
            }
    
            // If row is full, clear it and move everything above it down
            if (full) {
                for (int k =i; k >1;k--) { // Move each row down
                    for (int j = 1; j < WIDTH - 1; j++) {
                        map[k][j] = map[k - 1][j];
                    }
                }
    
                // Clear the top row after shifting
                for (int j = 1; j < WIDTH - 1; j++) {
                    map[1][j] = 0;
                }
    
                score += WIDTH - 2; // Increase score for full line
                i++; // Check the same row index again after shifting
            }
        }
    }
    
    void Reset(){
        gameover=false;
        score=0;
        for(int i=0; i<HEIGHT; i++){ //resetting the grid
            for(int j=0; j<WIDTH; j++){
                map[i][j]=0;
            }
        }
        tetris.createNewTetromino();
        tetris.RenderTetris();

    }
 
    int GameoverScreen(){
        system("cls");
        gotoxy(WIDTH , HEIGHT/2 - 3 );
        setColor(4);
        cout<<"GAME OVER!!";
        gotoxy(WIDTH+3 , HEIGHT/2 - 1 );
        setColor(2);
        cout<<"Score: ";
        cout<<"        Highest Score: ";

        gotoxy(WIDTH+1 , HEIGHT/2 + 1 );
        setColor(1);
        cout<<"Press E - Exit";
        gotoxy(WIDTH+1 , HEIGHT/2 + 2 );
        cout<<"Press R - Restart the game";
        setColor(7);

        char in=_getch();

        switch(in){
            case 'e':
                exit(0);
                break;
            case 'r':
                system("cls");
                return 1;
        }
        return 0;
    }

    int Score() { return score; }
};                      


Tetris t1;
Game game(t1);

void input(){
    if(_kbhit()){
        int ch=_getch();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // clear extra inputs

        if(ch==SPACE) t1.hardDrop();
        if(ch== ESC)  game.Pause();

        if(ch==224){ //for spacial characters(arrow keys) _getch() returns 2 values 
            ch=_getch();

            switch (ch){
                case KEY_UP:
                    t1.Rotate();
                    break;
                case KEY_DOWN:
                    t1.moveDown();
                    break;
                case KEY_LEFT:
                    t1.moveLeft();
                    break;
                case KEY_RIGHT:
                    t1.moveRight();
                    break;
               
            }
        }
    }
}




int main(){
    srand(time(0));
    HWND s = GetConsoleWindow(); //idea from stackoverflow
    MoveWindow(s, 300, 100, 480, 620, true);
    hideCursor();
    system("cls");

    gotoxy(WIDTH/2 -5, 1);
    cout<<"SCORE: "<<game.Score();
    gotoxy(WIDTH/2 +5, 1);
    cout<<"HIGHEST: "<<game.Score();
    
    
    while(true){
        while (! game.checkGameover()) {
            game.update();

            input();
        }
        if(game.GameoverScreen() ==1 ) game.Reset(); 
    }
    
    return 0;
}



