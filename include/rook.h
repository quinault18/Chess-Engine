#ifndef ROOK_H
#define ROOK_H

#include "basepiece.h"

class Rook : public BasePiece {

    public:  
        Rook(std::string id);
        ~Rook() override;
        std::vector<Move> getValidMoves(Board* board) override;

};

#endif