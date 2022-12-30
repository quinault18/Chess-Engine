#ifndef KNIGHT_H
#define KNIGHT_H

#include "basepiece.h"

class Knight : public BasePiece {

    public:  
        Knight(std::string id);
        ~Knight() override;
        std::vector<Move> getValidMoves(Board* board) override;

};

#endif