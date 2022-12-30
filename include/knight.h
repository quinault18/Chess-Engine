#ifndef KNIGHT_H
#define KNIGHT_H

#include "basepiece.h"

class Knight : public BasePiece {

    public:  

        /*
        Inherits the id property from BasePiece.
        Inherits the position property from BasePiece. This will be updated when a 
        move is made with this piece.
        */
        Knight(std::string id, std::tuple<int, int> position);
        ~Knight() override;

        /*
        Finds all valid moves for this knight. Knights can move in an 'L' pattern,
        and can not jump over pieces.
        The Board* is used to find other pieces on the board.

        This method is implemented in board.cpp.

        TODO - implement checks and pins
        */
        std::vector<Move> getValidMoves(Board* board) override;

};

#endif