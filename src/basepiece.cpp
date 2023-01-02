#include "basepiece.h"


BasePiece::BasePiece(std::string id) : id(id) {}


BasePiece::BasePiece(std::string id, std::tuple<int, int> pos) : id(id), position(pos) {}


BasePiece::BasePiece(const BasePiece& other) {
    id = other.id;
    directions = other.directions;
    position = other.position;
}

BasePiece& BasePiece::operator=(BasePiece other) {
    std::swap(id, other.id);
    std::swap(directions, other.directions);
    std::swap(position, other.position);

    return *this;
}

std::vector<Move> BasePiece::getValidMoves(Board* board)  {
    std::vector<Move> moves;
    return moves;
}

std::vector<Move> BasePiece::getAttackingMoves(Board* board)  {
    std::vector<Move> moves;
    return moves;
}


std::string BasePiece::getID() {
    return id;
}


std::tuple<int, int> BasePiece::getPosition() {
    return position;
}


void BasePiece::setPosition(std::tuple<int, int> newPos) {
    position = newPos;
}


