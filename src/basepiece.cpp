#include "basepiece.h"


BasePiece::BasePiece(std::string id) : id(id) {}


BasePiece::BasePiece(std::string id, std::tuple<int, int> pos) : id(id), position(pos) {}


std::vector<Move> BasePiece::getValidMoves(Board* board)  {
    std::vector<Move> moves;
    return moves;
}


std::string BasePiece::getID() {
    return id;
}


std::tuple<int, int> BasePiece::getPosition() {
    return position;
}


