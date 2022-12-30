#include "queen.h"


Queen::Queen(std::string id, std::tuple<int, int> position) : BasePiece(id, position) {
    
    // Queens can move any muptile of squares in any direction
    directions.push_back(std::make_tuple(1, 1));
    directions.push_back(std::make_tuple(1, -1));
    directions.push_back(std::make_tuple(-1, 1));
    directions.push_back(std::make_tuple(-1, -1));
    directions.push_back(std::make_tuple(1, 0));
    directions.push_back(std::make_tuple(0, 1));
    directions.push_back(std::make_tuple(-1, 0));
    directions.push_back(std::make_tuple(0, -1));
}


Queen::~Queen() {}
