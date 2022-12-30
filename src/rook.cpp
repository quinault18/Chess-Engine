#include "rook.h"

Rook::Rook(std::string id, std::tuple<int, int> position) : BasePiece(id, position) {

    // Rooks can move vertically and horizontally any number of squares
    directions.push_back(std::make_tuple(1, 0));
    directions.push_back(std::make_tuple(0, 1));
    directions.push_back(std::make_tuple(-1, 0));
    directions.push_back(std::make_tuple(0, -1));
}

Rook::~Rook() {}
