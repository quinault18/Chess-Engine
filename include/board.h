#ifndef BOARD_H
#define BOARD_H


#include "square.h"
#include <iostream>
#include <vector>

class Board {

private:

    // 8x8 vector of Squares to represent the board
    std::vector<std::vector<Square> > board;

    bool whiteToPlay;

    // Helper method for loading the board from a FEN string
    std::vector<std::string> parseFEN(std::string fen);

    // Helper method for initializing the board
    void initBoard();



public:

    // Default constructor - loads 8x8 board of empty squares
    Board();

    // If a FEN string is passed, load the board with the passed string
    Board(std::string fen);

    // Loads the board from a FEN string
    void loadFromFEN(std::string fen);

    // Print out representation of board
    void print();

    // Return 8x8 board
    std::vector<std::vector<Square> > getBoard();

    // Overloading access operator []
    std::vector<Square>& operator[](int idx);

    // Getter for whiteToPlay
    bool getWhiteToPlay();



};

#endif