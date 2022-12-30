#include "knight.h"

Knight::Knight(std::string id, std::tuple<int, int> position) : BasePiece(id, position) {

    // Knights  move in an 'L' pattern
    directions.push_back(std::make_tuple(2, 1));
    directions.push_back(std::make_tuple(1, 2));
    directions.push_back(std::make_tuple(-1, 2));
    directions.push_back(std::make_tuple(-2, 1));
    directions.push_back(std::make_tuple(-2, -1));
    directions.push_back(std::make_tuple(-1, -2));
    directions.push_back(std::make_tuple(1, -2));
    directions.push_back(std::make_tuple(2, -1));
}

Knight::~Knight() {}

