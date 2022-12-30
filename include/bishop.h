#ifndef BISHOP_H
#define BISHOP_H

#include "basepiece.h"

class Bishop : public BasePiece {

    public: 
    
        /*
        Inherits the id property from BasePiece.
        Inherits the position property from BasePiece. This will be updated when a 
        move is made with this piece.
        */ 
        Bishop(std::string id, std::tuple<int, int> position);
        ~Bishop() override;

        /*
        Finds all valid moves for this bishop. Bishops can move diagonally
        an unlimited number of squares, but can not jump over pieces.
        The Board* is used to find other pieces on the board.

        This method is implemented in board.cpp.

        TODO - implement checks and pins
        */
        std::vector<Move> getValidMoves(Board* board) override;

};

#endif