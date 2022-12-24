#include "queen.h"


Queen::Queen(std::string id) : BasePiece(id) { std::cout << "Queen" << std::endl; }

Queen::~Queen() {}

std::vector<Move> Queen::getValidMoves() {
    std::vector<Move> moves;

    return moves;
}