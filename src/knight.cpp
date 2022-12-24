#include "knight.h"

Knight::Knight(std::string id) : BasePiece(id) { std::cout << "Knight" << std::endl; }

Knight::~Knight() {}

std::vector<Move> Knight::getValidMoves() {
    std::vector<Move> moves;
    return moves;
}