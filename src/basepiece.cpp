#include "basepiece.h"

BasePiece::BasePiece(std::string id) : id(id) {}

std::vector<Move> BasePiece::getValidMoves()  {
    std::vector<Move> moves;
    return moves;
}

std::string BasePiece::getID() {
    return id;
}

