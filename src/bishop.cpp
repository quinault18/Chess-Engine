#include "bishop.h"

Bishop::Bishop(std::string id) : BasePiece(id) { std::cout << "Bishop" << std::endl; }

Bishop::~Bishop() {}

std::vector<Move> Bishop::getValidMoves(Board* board) {
    std::vector<Move> moves;
    return moves;
}