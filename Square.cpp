#include "Arduino.h"
#include "Square.h"

Square::Square(int x, int y)
{
    piece = EMPTY;
    color = NONE;
    // x = x;
    // y = y;
}

void Square::setX(int ex)
{
    x = ex;
}

int Square::getX()
{
    return x;
}

void Square::setY(int ey)
{
    y = ey;
}

int Square::getY()
{
    return y;
}

void Square::setPieceAndColor(Piece p, Color c)
{
    piece = p;
    color = c;
}

Piece Square::getPiece()
{
    return piece;
}

Color Square::getColor()
{
    return color;
}

void Square::setSpace(Square *space)
{
    color = space->getColor();
    piece = space->getPiece();
}

void Square::setEmpty()
{
	piece = EMPTY;
	color = NONE;
}
