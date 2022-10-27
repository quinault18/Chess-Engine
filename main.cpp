#include "board.h"
#include <iostream>

int main() {

    Board board;

    board.loadFromFEN("r4rk1/1pqnbpp1/2p1pn1p/p6P/2PP4/3Q1NN1/PP1B1PP1/1K1RR3 w - - 0 18");

    board.print();

    return 0;
 
}