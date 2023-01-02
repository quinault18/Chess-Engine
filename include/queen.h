#ifndef QUEEN_H
#define QUEEN_H

#include "basepiece.h"

class Queen : public BasePiece {

public: 

    /*
    Inherits the id property from BasePiece.
    Inherits the position property from BasePiece. This will be updated when a 
    move is made with this piece.
    */
    Queen(std::string id, std::tuple<int, int> position);
    ~Queen() override;

    /*
    Finds all valid moves for this queen. Queens can move in all directions 
    an unlimited number of squares, but can not jump over pieces.
    The Board* is used to find other pieces on the board.

    This method is implemented in board.cpp.

    TODO - implement checks and pins
    */
    std::vector<Move> getValidMoves(Board* board) override;
    std::vector<Move> getAttackingMoves(Board* board) override;
};

#endif