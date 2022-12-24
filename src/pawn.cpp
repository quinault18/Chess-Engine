#include "pawn.h"

Pawn::Pawn(std::string id) : BasePiece(id) { std::cout << "Pawn" << std::endl; }

Pawn::~Pawn() {}

std::vector<Move> Pawn::getValidMoves() {
    std::vector<Move> moves;
    return moves;
}