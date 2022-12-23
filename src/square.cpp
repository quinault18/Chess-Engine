#include "square.h"

Square::Square(int rank, int file) {
    location = std::make_tuple(rank, file);
}

std::tuple<int, int> Square::getLocation() {
    return location;
}