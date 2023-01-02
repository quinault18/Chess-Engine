#ifndef KING_H
#define KING_H

#include "basepiece.h"

class King : public BasePiece {

    private:
        std::vector<Move> getCastlingMoves(Board* board);
        std::vector<Move> getKingSideCastlingMoves(Board* board);
        std::vector<Move> getQueenSideCastlingMoves(Board* board);

    public:

        /*
        Inherits the id property from BasePiece.
        Inherits the position property from BasePiece. This will be updated when a 
        move is made with this piece.
        */
        King(std::string id, std::tuple<int, int> position);
        ~King() override;

        /*
        Finds all valid moves for this king. A valid move means the move can be played 
        without considering checks. Kings can move any direction one square.
        The Board* is used to find other pieces on the board.

        This is implemented in board.cpp.
        */
        std::vector<Move> getValidMoves(Board* board) override;
        std::vector<Move> getAttackingMoves(Board* board) override;
    
};

#endif