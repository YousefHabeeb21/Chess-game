#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

using namespace std;


enum Color {
    White,
    Black,
    None
};

enum Piece {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    EMPTY
};


// used to classify the chess piece
struct ChessPiece {
    Color color;
    Piece piece;
};

class Chessboard;


// declaration of all iterator processes used in the chessboard.cpp
class ChessboardIterator {
private:
    int x, y;
    Chessboard& chessboard;

public:
    // declaration of all iterator and operators
    ChessboardIterator(int x, int y, Chessboard& board);
    ChessboardIterator& operator++();
    int xy(int& x, int& y);
    bool operator==(const ChessboardIterator& other) const;
    bool operator!=(const ChessboardIterator& other) const;
    ChessPiece& operator*();
};





class Chessboard {
private:
    ChessPiece board[8][8];

public:

    // Constructor to initialize the board
    Chessboard(); 

    friend class ChessboardIterator;
    ChessboardIterator begin();
    ChessboardIterator end();
    
    // used for creating an empty space after a piece is moved
    void clear(int x, int y);

    // placing the piece on the board
    int place(int x, int y, Color c, Piece p);
   
    // returning the values of the piece
    int get(int x, int y, Color &c, Piece &p);

    // rules for the rook
    int rookValidMoves(int fromX, int fromY, int toX, int toY);

    // rules for the knight
    int knightValidMoves(int fromX, int fromY, int toX, int toY);
    
    // rules for the bishop
    int bishopValidMoves(int fromX, int fromY, int toX, int toY);
   
   // rules for the Pawn
    int pawnValidMoves(int fromX, int fromY, int toX, int toY);
    
    // rules for he king 
    int kingValidMoves (int fromX, int fromY, int toX, int toY);
    
    // rules for the queen
    int queenValidMoves(int fromX, int fromY, int toX, int toY) ;
   
   // checking what piece is being moved 
    int validMoves(int fromX, int fromY, int toX, int toY);

    // checks all validation functions and then moves the piece 
    int move(int fromX, int fromY, int toX, int toY);


    void print(); 
    
};
#endif // CHESSBOARD_H