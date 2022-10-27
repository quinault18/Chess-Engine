#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
    /*
    
    Represents a square on the chess board. A square contains a Piece, which if the square
    is empty, the piece is nullptr.
    
    */

    public:
        Piece* piece;
        Square(Piece*);

};

#endif 
