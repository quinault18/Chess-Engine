#ifndef PAWN_H
#define PAWN_H

#include "basepiece.h"

class Pawn : public BasePiece {

    public: 
        Pawn(std::string id, std::tuple<int, int> position);
        ~Pawn() override;
        std::vector<Move> getValidMoves(Board* board) override;
};

#endif