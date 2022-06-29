#include "Arduino.h"
#include "Board.h"
#include "Square.h"

Board::Board(int x)
{
    // memory allocate
    square = (Square **)malloc(8 * sizeof(*square));
    for (int i = 0; i < 8; i++)
    {
        square[i] = (Square *)malloc(8 * sizeof(*square[i]));
    }

    turn = WHITE;
}

void Board::setBoard()
{
    square[0][0].setPieceAndColor(ROOK, WHITE);
    square[1][0].setPieceAndColor(KNIGHT, WHITE);
    square[2][0].setPieceAndColor(BISHOP, WHITE);
    square[3][0].setPieceAndColor(QUEEN, WHITE);
    square[4][0].setPieceAndColor(KING, WHITE);
    square[5][0].setPieceAndColor(BISHOP, WHITE);
    square[6][0].setPieceAndColor(KNIGHT, WHITE);
    square[7][0].setPieceAndColor(ROOK, WHITE);

    square[0][7].setPieceAndColor(ROOK, BLACK);
    square[1][7].setPieceAndColor(KNIGHT, BLACK);
    square[2][7].setPieceAndColor(BISHOP, BLACK);
    square[3][7].setPieceAndColor(QUEEN, BLACK);
    square[4][7].setPieceAndColor(KING, BLACK);
    square[5][7].setPieceAndColor(BISHOP, BLACK);
    square[6][7].setPieceAndColor(KNIGHT, BLACK);
    square[7][7].setPieceAndColor(ROOK, BLACK);

    for (int i = 0; i < 8; i++)
    {
        square[i][1].setPieceAndColor(PAWN, WHITE);
        square[i][6].setPieceAndColor(PAWN, BLACK);
    }
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
            square[j][i].setPieceAndColor(EMPTY, NONE);
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            square[i][j].setX(i);
            square[i][j].setY(j);
        }
}

Square *Board::getSquare(int x, int y)
{
    return &square[x][y];
}

void Board::setSquare(Square *s, int x, int y)
{
    square[x][y] = *s;
}

bool Board::moveKing(Square *thisKing, Square *thatSpace)
{
    // off board inputs should be handled elsewhere (before this)
    // squares with same color should be handled elsewhere (before this)
    if (abs(thatSpace->getX() - thisKing->getX()) == 1)
        if (abs(thatSpace->getY() - thisKing->getY()) == 1)
        {
            thatSpace->setSpace(thisKing);
            thisKing->setEmpty();
            return true;
        }
        else
            return false;
    else
        return false;
}

bool Board::moveQueen(Square *thisQueen, Square *thatSpace)
{ // there might be problems with numbers of brackets
    // off board inputs should be handled elsewhere (before this)
    // squares with same color should be handled elsewhere (before this)

    int queenX = thisQueen->getX();
    int queenY = thisQueen->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    // std::cout << "this";
    int yIncrement;
    int xIncrement;

    bool invalid = false;
    if (queenX != thatX || queenY != thatY)
    {

        if (queenX == thatX)
        {
            yIncrement = (thatY - queenY) / (abs(thatY - queenY));
            for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
            {

                if (square[thatX][i].getColor() != NONE)
                    return false;
            }
        }
        else if (queenY == thatY)
        {

            xIncrement = (thatX - queenX) / (abs(thatX - queenX));
            for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
            {
                if (square[i][thatY].getColor() != NONE)
                    return false;
            }
        }
        else if (abs(queenX - thatX) == abs(queenY - thatY))
        {
            xIncrement = (thatX - queenX) / (abs(thatX - queenX));
            yIncrement = (thatY - queenY) / (abs(thatY - queenY));

            for (int i = 1; i < abs(queenX - thatX); i++)
            {
                // std::cout << "It got here somehow";
                if (square[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
                    return false;
            }
        }
        else
            return false;
        // if()
    }

    if (invalid == false)
    {
        thatSpace->setSpace(thisQueen);
        thisQueen->setEmpty();
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::moveBishop(Square *thisBishop, Square *thatSpace)
{ // there might be problems with number of brackets
    int bishopX = thisBishop->getX();
    int bishopY = thisBishop->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    bool invalid = false;
    Square *s;
    if (abs(bishopX - thatX) == abs(bishopY - thatY))
    {
        int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
        int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

        for (int i = 1; i < abs(bishopX - thatX); i++)
        {
            // std::cout << "It got here somehow";
            if (square[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
                return false;
        }
    }
    else
        return false;

    if (invalid == false)
    {
        thatSpace->setSpace(thisBishop);
        thisBishop->setEmpty();
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::moveKnight(Square *thisKnight, Square *thatSpace)
{
    // off board inputs should be handled elsewhere (before this)
    // squares with same color should be handled elsewhere (before this)
    int knightX = thisKnight->getX();
    int knightY = thisKnight->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();

    if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
    {
        thatSpace->setSpace(thisKnight);
        thisKnight->setEmpty();
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::moveRook(Square *thisRook, Square *thatSpace)
{
    // off board inputs should be handled elsewhere (before this)
    // squares with same color should be handled elsewhere (before this)
    int rookX = thisRook->getX();
    int rookY = thisRook->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    bool invalid = false;
    if (rookX != thatX || rookY != thatY)
    {

        if (rookX == thatX)
        {
            int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
            for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
            {

                if (square[thatX][i].getColor() != NONE)
                    return false;
            }
        }
        else if (rookY == thatY)
        {

            int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
            for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
            {
                if (square[i][thatY].getColor() != NONE)
                    return false;
            }
        }
        else
            return false;
    }
    if (invalid == false)
    {
        thatSpace->setSpace(thisRook);
        thisRook->setEmpty();
        return true;
    }
    else
    { // Return some erorr or something. Probably return false;
        // std::cout << "That is an invalid move for rook";
        return false;
    }
}

bool Board::movePawn(Square *thisPawn, Square *thatSpace)
{
    // off board inputs should be handled elsewhere (before this)
    // squares with same color should be handled elsewhere (before this)
    using namespace std;
    bool invalid = false;
    int pawnX = thisPawn->getX();
    int pawnY = thisPawn->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();

    if (thisPawn->getColor() == WHITE)
    {

        if (pawnX == thatX && (thatY == pawnY + 1 || thatY == pawnY + 2) && thatSpace->getColor() == NONE)
        {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
        else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && thatSpace->getColor() == BLACK)
        {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
        else
            return false;
    }
    else if (thisPawn->getColor() == BLACK)
    {
        if (pawnX == thatX && (thatY == pawnY - 1 || thatY == pawnY - 2) && thatSpace->getColor() == NONE)
        {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
        else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && thatSpace->getColor() == WHITE)
        {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool Board::makeMove(int x1, int y1, int x2, int y2)
{
    // Checking for turns will be done previous to this
    // using namespace std;
    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 8)
    {
        // std::cout << "One of your inputs was out of bounds" << std::endl;
        return false;
    }
    Square *src = getSquare(x1, y1);
    Square *dest = getSquare(x2, y2);

    if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
    {
        // std::cout << "Invalid move: cannot land on your own piece" << std::endl;
        return false;
    }

    switch (src->getPiece())
    {
    case KING:
        return moveKing(src, dest);
        break;
    case QUEEN:
        return moveQueen(src, dest);
        break;
    case BISHOP:
        return moveBishop(src, dest);
        break;
    case KNIGHT:
        return moveKnight(src, dest);
        break;
    case ROOK:
        return moveRook(src, dest);
        break;
    case PAWN:
        return movePawn(src, dest);
        break;
    case EMPTY:
        // std::cout << "You do not have a piece there" << std::endl;
        return false;
        break;
    default:
        // std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
        break;
    }
    return false;
}

Color Board::checkCheckMate()
{
    bool whiteWin = true;
    bool blackWin = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (square[i][j].getPiece() == KING)
            {
                if (square[i][j].getColor() == WHITE)
                {
                    blackWin = false;
                }
                if (square[i][j].getColor() == BLACK)
                {
                    whiteWin = false;
                }
            }
        }
    }
    if (whiteWin)
        return WHITE;
    else if (blackWin)
        return BLACK;
    else
        return NONE;
}

// double Board::boardValueEvaluation()
// {
//     for (int i = 0; i < 8; i++)
//     {
//         for (int j = 0; j < 8; j++)
//         {
//         }
//     }
// }