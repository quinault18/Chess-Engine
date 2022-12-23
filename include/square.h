#ifndef SQUARE_H
#define SQUARE_H

#include <tuple>

class Square {
private:
    std::tuple<int, int> location;

public:

    Square(int rank, int file);
    std::tuple<int, int> getLocation();

};

#endif
