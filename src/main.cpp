
//#include "basepiece.h"
#include "board.h"
#include <iostream>


// Dummy main for compilation purposes
int main() {
    Board b("3rk3/8/8/8/8/8/8/3K4 w - - 0 1");

    std::vector<Move> all = b.generateAllMoves();
    std::vector<Move> moves = b.generateMoves();

    std::cout << all.size() << std::endl << moves.size() << std::endl;

    return 0;
}