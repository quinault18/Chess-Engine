#include "king.h"

King::King(std::string id) : BasePiece(id) {std::cout << "King" << std::endl;}

King::~King() {}

std::vector<Move> King::getValidMoves(Board* board) {
    std::vector<Move> moves; 
    return moves;
}