#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "piece.h"
#include <vector> 
#include <iostream>
#include <string>

class Board {
    /*
    
    Represents an 8x8 Square chessboard. 

    */

    private:
        std::vector<std::string> parseFEN(std::string);
        bool whiteToPlay;

    public: 
    
        std::vector<std::vector<Square> > board;
        
        Board();

        void loadFromFEN(std::string);
        void print();

};

#endif