#ifndef board_h
#define board_h
#include "Arduino.h"
#include "Square.h"

double kingPositionValue[8][8] = 
{
    -3.0, -3.0, -3.0, -3.0, -2.0, -1.0, 2.0, 2.0,
    -4.0, -4.0, -4.0, -4.0, -3.0, -2.0, 2.0, 3.0,
    -4.0, -4.0, -4.0, -4.0, -3.0, -2.0, 0.0, 1.0,
    -5.0, -5.0, -5.0, -5.0, -4.0, -2.0, 0.0, 0.0,
    -5.0, -5.0, -5.0, -5.0, -4.0, -2.0, 0.0, 0.0,
    -4.0, -4.0, -4.0, -4.0, -3.0, -2.0, 0.0, 1.0,
    -4.0, -4.0, -4.0, -4.0, -3.0, -2.0, 2.0, 3.0,
    -3.0, -3.0, -3.0, -3.0, -2.0, -1.0, 2.0, 2.0,
};

class Board
{
public:
    Board(int x);
    void setBoard();
    Square *getSquare(int x, int y);
    void setSquare(Square *s, int x, int y);
    bool makeMove(int x1, int y1, int x2, int y2);
    Color checkCheckMate();
    double boardValueEvaluation();
private:
    Square **square;
    Color turn;
    bool moveKing(Square *thisKing, Square *thatSpace);
    bool moveQueen(Square *thisQueen, Square *thatSpace);
    bool moveBishop(Square *thisBishop, Square *thatSpace);
    bool moveKnight(Square *thisKnight, Square *thatSpace);
    bool moveRook(Square *thisRook, Square *thatSpace);
    bool movePawn(Square *thisPawn, Square *thatSpace);
    
};
#endif