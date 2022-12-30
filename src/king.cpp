#include "king.h"

King::King(std::string id, std::tuple<int, int> position) : BasePiece(id, position) {
    
    // Kings can move any direction one square
    directions.push_back(std::make_tuple(1, 1));
    directions.push_back(std::make_tuple(1, -1));
    directions.push_back(std::make_tuple(-1, 1));
    directions.push_back(std::make_tuple(-1, -1));
    directions.push_back(std::make_tuple(1, 0));
    directions.push_back(std::make_tuple(0, 1));
    directions.push_back(std::make_tuple(-1, 0));
    directions.push_back(std::make_tuple(0, -1));
}

King::~King() {}
