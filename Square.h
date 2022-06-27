#ifndef square_h
#define square_h
#include "Arduino.h" 
enum Piece
{
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN,
	EMPTY
};
enum Color
{
	WHITE,
	BLACK,
	NONE
};
class Square {
public:
    // constructor, note that Arduino need none-void argument
	Square(int x, int y);

    // get and set inside value
    void setX(int ex);
    int getX();
    void setY(int ey);
    int getY();
    void setPieceAndColor(Piece, Color);
    Piece getPiece();
	Color getColor();

    // tool function
    void setSpace(Square *);
    void setEmpty();

private:
    Piece piece;
	Color color;
	int x, y;
};
#endif