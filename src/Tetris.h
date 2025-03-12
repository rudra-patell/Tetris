#ifndef Tetris_H
#define Tetris_H

#include <vector>

class Tetris {
public:
    struct Tetromino {
        char type;
        std::vector<std::vector<int>> shape;
        int color;
        Tetromino(char t, std::vector<std::vector<int>> s, int c);
    };

    int x, y;
    bool spwancollision;
    std::vector<Tetromino> tetrominoes;
    Tetromino tetromino;

    Tetris();
    void Rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void hardDrop();
    bool isCollision(int dx, int dy);
    void merge();
    int createNewTetromino();
    void RenderTetris();
    bool currTetromino();
};

#endif