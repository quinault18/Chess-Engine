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

    /**
     * @brief Construct a new Square object. Squares take in a (rank, file) location and a piece
     * 
     * @param rank - integer location of the rank of this square
     * @param file - integer location of the file of this square
     * @param piece - pointer to a BasePiece that occupies this square
     */
    Square(int rank, int file, BasePiece* piece = nullptr);

    /*
    Rule of Three implementation
    */
    ~Square();
    Square(const Square& other);
    Square& operator=(Square other);
    
    /*
    Equality operator overloading
    */
    bool operator==(const Square other) const;
    bool operator!=(const Square other) const;

    /**
     * @brief Returns (rank, file) location of this square
     * 
     * @return std::tuple<int, int> - location of this square
     */
    std::tuple<int, int> getLocation();

    /**
     * @brief Returns the piece on this square
     * 
     * @return BasePiece* - pointer to the piece on this square
     */
    BasePiece* getPiece();

    /**
     * @brief Setup setting pieces
     * 
     * @param pieceToSet 
     */
    void setPieceAtStart(BasePiece* pieceToSet);
    
    /**
     * @brief Sets the BasePiece* on this square
     * 
     * @param pieceToSet - BasePiece* to be on this square
     */
    void setPiece(BasePiece* pieceToSet);
};

#endif
