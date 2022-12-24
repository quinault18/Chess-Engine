#ifndef BASEPIECE_H
#define BASEPIECE_H

#include <vector>
#include <string>
#include <iostream>
#include "move.h"


class BasePiece {
    private:
        std::string id;

    public: 
        BasePiece(std::string id);
        virtual ~BasePiece() = default;
        std::string getID();

        // Method for generating the valid moves a piece has
        virtual std::vector<Move> getValidMoves();

    
};

#endif