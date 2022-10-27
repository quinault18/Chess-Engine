#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece {
    /*
    
    Represents a piece on the chessboard. Pieces include:
        Pawns
        Knights
        Bishops
        Rooks
        Queens
        Kings
    */

    public:
        std::string id;
        Piece(std::string);

};

#endif