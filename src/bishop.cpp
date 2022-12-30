#include "bishop.h"

Bishop::Bishop(std::string id, std::tuple<int, int> position) : BasePiece(id, position) {
    // Bishops can move diagonally any number of squares
    directions.push_back(std::make_tuple(1, 1));
    directions.push_back(std::make_tuple(1, -1));
    directions.push_back(std::make_tuple(-1, 1));
    directions.push_back(std::make_tuple(-1, -1));
}

Bishop::~Bishop() {}

