#include "rook.h"

Rook::Rook(std::string id) : BasePiece(id) { std::cout << "Rook" << std::endl; }

Rook::~Rook() {}

std::vector<Move> Rook::getValidMoves() {
    std::vector<Move> moves;
   
    return moves;
}