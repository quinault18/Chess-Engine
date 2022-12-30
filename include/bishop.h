#ifndef BISHOP_H
#define BISHOP_H

#include "basepiece.h"

class Bishop : public BasePiece {

    public:  
        Bishop(std::string id);
        ~Bishop() override;
        std::vector<Move> getValidMoves(Board* board) override;

};

#endif