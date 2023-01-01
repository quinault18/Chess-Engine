
//#include "basepiece.h"
#include "board.h"
#include <iostream>


// Dummy main for compilation purposes
int main() {

    Board board("r2qk2r/1ppb1ppp/p1np1n2/2b1p1B1/2B1P3/2NP4/PPPQ1PPP/R3K1NR w KQkq - 1 8");

    std::vector<Move> moves = board.generateMoves();
    for (Move move : moves) {
        if (move.isCastleMove) {
            board.makeMove(move);
            break;
        }
    }

    board.print();
    std::cout << board.toFEN() << std::endl;
    return 0;
}