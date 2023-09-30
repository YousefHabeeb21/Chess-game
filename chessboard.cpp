#include "chessboard.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>


using namespace std;

//constructor for the board
Chessboard::Chessboard(){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].color = None;
            board[i][j].piece = EMPTY;
        }
    }
}
// clears the old piece after chnaging locations 
void Chessboard::clear(int x, int y){
    
    board[y][x].color = None;
    board[y][x].piece = EMPTY;

}


// places the piece after validation
int Chessboard::place(int x, int y, Color c, Piece p) {
        
    if (x > 7 || x < 0){
        return -1;
    }
    if (y > 7 || y < 0){
        return -2;
    }

    if(board[y][x].piece != EMPTY){
        return -3;
    }
    if(c != White && c != Black){
        return -4;
    }
    if(p != King && p != Queen && p != Knight && p != Bishop && p != Rook && p != Pawn){
        return -5;
    }

    board[y][x].color = c;
    board[y][x].piece = p;

    return 1;
}



// returning the information of the sqaure on the board
int Chessboard::get(int x, int y, Color &c, Piece &p){
    if (x > 7 || x < 0){
        return -1;
    }
    if (y > 7 || y < 0){
        return -2;
    }
    if(board[y][x].piece == EMPTY){
        return -3;
    }

    c = board[y][x].color;
    p = board[y][x].piece;
    return 1;
}





// valid rook moves are being checked off
int Chessboard::rookValidMoves(int fromX, int fromY, int toX, int toY) {

    // moving vertically
    if (toX == fromX && toY != fromY) {
        int distance = abs(toY-fromY);
        for (int i = fromY + 1; i < distance; i++) {
            if (board[i][toX].piece != EMPTY) {
                return -7;
            }
        }
    }

    // moving horizontally 
    if (toX != fromX && toY == fromY) {
        int distance = abs(toX-fromX);
        for (int i = fromX + 1; i < distance; i++) {
            if (board[toY][i].piece != EMPTY) {
                return -7;
            }
        }
    }
    return 1;
}



// valid knight moves being checked 
int Chessboard::knightValidMoves(int fromX, int fromY, int toX, int toY){

    // moving up 1 / right or left 
    if(fromX == (2 + toX)||fromX == (toX - 2)){
        if (fromY == (toY - 1) || fromY == (toY + 1)){
            return 1;
        }
    }
    // moving up 2 / right or left
    if(fromX == (1 + toX)||fromX == (toX - 1)){
        if (fromY == (toY - 2) || fromY == (toY + 2)){
            return 1;
        }
    }
    return -7;
}



// valid bishop moves being checked
int Chessboard::bishopValidMoves(int fromX, int fromY, int toX, int toY){
        
    int distanceX = abs(toX - fromX);
    int distanceY = abs(toY - fromY);

    if (distanceX != distanceY) {
        return -7; 
    } 

    // steps used for checking if there is a piece in the way of the destination
    int stepX;
    if(toX > fromX) { stepX = 1; }
    else { stepX = -1; }     

    int stepY;
    if (toY > fromY) { stepY = 1; }
    else { stepY = -1; }


    for (int i = 1; i < distanceX; i++) {
        int currentX = fromX + i * stepX;
        int currentY = fromY + i * stepY;

    
        if (board[currentY][currentX].color != None && board[currentY][currentX].piece != EMPTY) {
            return -7; 
        }
    }
        
    return 1;
}





// valid queen moves being checked 
int Chessboard::queenValidMoves(int fromX, int fromY, int toX, int toY){

    // the queens valid moves consist of the rooks and bishops
    int p = rookValidMoves(fromX, fromY,  toX, toY);

    if (p != 1){
        p = bishopValidMoves(fromX, fromY,  toX, toY);
    }
    return p;
}




// valid moves for the king being checked
int Chessboard::kingValidMoves(int fromX, int fromY, int toX, int toY){

    int distanceX = abs(fromX - toX);

    int distanceY = abs(fromY - toY);

    if ( distanceX <= 1 && distanceY <=1){
        return 1;
    }

    return -7;
}



// valid moves for the pawn being checked
int Chessboard::pawnValidMoves(int fromX, int fromY, int toX, int toY){
        
    // the pawn mcan only move down if the color is black 
    if(board[fromY][fromX].color == Black){
        if (fromX == toX && fromY - 1 == toY){
            if(board[toY][toX].piece == EMPTY){
                return 1;
            }
        }
        // initial move can be 2 spaces
        if (fromX == toX && fromY - 2 == toY && fromY == 6) {
            if(board[toY][toX].piece == EMPTY){
                return 1;
            } 
        }
        // Valid diagonal capture move
        if (abs(toX - fromX) == 1 && fromY - 1 == toY) {
            return 1; 
        }
    }
    // white pawn moves up only
    if(board[fromY][fromX].color == White){
        if (fromX == toX && fromY + 1 == toY){
            if(board[toY][toX].piece == EMPTY){
                return 1;
            }
        }
        if (fromX == toX && fromY + 2 == toY && fromY == 1) {
            if(board[toY][toX].piece == EMPTY){
                return 1;
            }
        }
        if (abs(toX - fromX) == 1 && fromY + 1 == toY) {
            return 1; 
        }
    }

    return -7;
}





// function to check which piece is being moved 
int Chessboard::validMoves(int fromX, int fromY, int toX, int toY){
    if(board[fromY][fromX].piece == Rook){
        return rookValidMoves(fromX,fromY,toX,toY);
    }

    if (board[fromY][fromX].piece == Knight){
        return knightValidMoves(fromX,fromY,toX,toY);
    }

    if (board[fromY][fromX].piece == Bishop){
        return bishopValidMoves(fromX,fromY,toX,toY);
    }

    if (board[fromY][fromX].piece == Pawn){
        return pawnValidMoves(fromX,fromY,toX,toY);
    }

    if (board[fromY][fromX].piece == King){
        return kingValidMoves(fromX,fromY,toX,toY);
    }

    if (board[fromY][fromX].piece == Queen){
        return queenValidMoves(fromX,fromY,toX,toY);
    }

    return -7;
}



// function that calls all validations and moves the piece
int Chessboard::move(int fromX, int fromY, int toX, int toY) {
    if (fromX > 7 || fromX < 0){
        return -1;
    }
    if (fromY > 7 || fromY < 0){
        return -2;
    }
    if (toX > 7 || toX < 0){
        return -3;
    }
    if (toY > 7 || toY < 0){
        return -4;
    }
    //the box thats chosen is empty 
    if (board[fromY][fromX].piece == EMPTY){
        return -5;
    }

    // cannot land on your own peices 
    if(board[toY][toX].piece != EMPTY && board[toY][toX].color == board[fromY][fromX].color){
        return -6;
    }

    int get = validMoves(fromX,fromY,toX,toY);

    if(get == 1){
        board[toY][toX].color = board[fromY][fromX].color;
        board[toY][toX].piece = board[fromY][fromX].piece;
        clear(fromX,fromY);
    }
    return get;
}



// implementation of the iterator
ChessboardIterator::ChessboardIterator(int x, int y,Chessboard& board) : x(x), y(y), chessboard(board){}

// inmcrementing iterator to the next position 
ChessboardIterator& ChessboardIterator::operator++() {
    if (x < 7) {
        x++;
    } else {
        x = 0;
        y++;
    }
    return *this;
}


int ChessboardIterator::xy(int& x, int& y) {

    // Set the x and y variables to the current iterator position.
    x = this->x;
    y = this->y;

    // Check if the iterator is on the board.
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return 1; 
    } else {
        return -1; 
    }
}

// Compare two iterators for equality.
bool ChessboardIterator::operator==(const ChessboardIterator& other) const {
    return x == other.x && y == other.y;
}

 // Compare two iterators for inequality.
bool ChessboardIterator::operator!=(const ChessboardIterator& other) const {
    return !(*this == other);
}

//dereference operator 
ChessPiece& ChessboardIterator::operator*() {
    return chessboard.board[y][x];
}

//start point 
ChessboardIterator Chessboard::begin() {
    return ChessboardIterator(0, 0,*this);
}

// end point 
ChessboardIterator Chessboard::end() {
    return ChessboardIterator(0, 8,*this); 
}


// printing the board using the iterator 
void Chessboard::print() {
    for (ChessboardIterator it = begin(); it != end(); ++it) {
        int currentX, currentY;
        if (it.xy(currentX, currentY) == 1) {
            int reversedY = 7 - currentY; // Reverse the y-coordinate

            Color c;
            Piece p;

            // Check for valid pieces
            int n = get(currentX, reversedY, c, p);
            if (n != 1){ cout << ' ' << '.' << ' '; }
            else {
                char colorChar;

                if (c == White) {
                    colorChar = 'w';
                } else if (c == Black) {
                    colorChar = 'b';
                }

                char pieceChar;
                switch (p) {
                    case King: pieceChar = 'K'; break;
                    case Queen: pieceChar = 'Q'; break;
                    case Rook: pieceChar = 'R'; break;
                    case Bishop: pieceChar = 'B'; break;
                    case Knight: pieceChar = 'N'; break;
                    case Pawn: pieceChar = 'P'; break;
                }
                cout << colorChar << pieceChar << " ";
            }
        }
        // Newline character at the end of each row.
        if (it.xy(currentX, currentY) == 1 && currentX == 7) {
            cout << endl;
        }
    }
}





