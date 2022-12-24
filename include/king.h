#ifndef KING_H
#define KING_H

#include "basepiece.h"

class King : public BasePiece {

    public:
        King(std::string id);
        ~King() override;
        std::vector<Move> getValidMoves() override;
    
};

#endif