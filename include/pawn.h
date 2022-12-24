#ifndef PAWN_H
#define PAWN_H

#include "basepiece.h"

class Pawn : public BasePiece {

    public: 
        Pawn(std::string id);
        ~Pawn() override;
        std::vector<Move> getValidMoves() override;
};

#endif