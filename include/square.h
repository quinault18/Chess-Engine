#ifndef SQUARE_H
#define SQUARE_H

#include <tuple>
#include "basepiece.h"
#include "queen.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"

class Square {
private:

    // Chessboard squares have a location in form (rank, file)
    std::tuple<int, int> location;
    // Squares store a piece. If square is empty, piece is nullptr
    BasePiece* piece;

public:

    // Squares take in a (rank, file) location and a piece
    Square(int rank, int file, BasePiece* piece = nullptr);

    ~Square();
    
    Square(const Square& other);

    Square& operator=(Square other);
    
    // Returns (rank, file) location of this square
    std::tuple<int, int> getLocation();

    // Returns the piece on this square
    BasePiece* getPiece();

    // Set the piece of this square
    void setPiece(BasePiece* pieceToSet);
};

#endif
