#ifndef BOARD_H
#define BOARD_H


#include "square.h"
#include <iostream>
#include <vector>

class Board {

private:

    // 8x8 vector of Squares to represent the board
    std::vector<std::vector<Square> > board;

    // Active color
    bool whiteToPlay;

    // Castling rights
    std::string castlingRights;

    // En Passant targets
    std::string enPassantTargets;

    // Halfmove and full move count
    int halfMove;
    int moveNumber;

    // Helper method for loading the board from a FEN string
    std::vector<std::string> parseFEN(std::string fen);

    // Helper method for initializing the board
    void initBoard();



public:

    // Default constructor - loads 8x8 board of empty squares
    Board();

    // If a FEN string is passed, load the board with the passed string
    Board(std::string fen);

    /*
    Rule of Three implementation
    */
    ~Board();
    Board(const Board& other);
    Board& operator=(Board otherr);

    /*
    Equality operator overloading
    */
    friend bool operator==(const Board& lhs, const Board& rhs);
    friend bool operator!=(const Board& lhs, const Board& rhs);

    // Loads the board from a FEN string
    void loadFromFEN(std::string fen);

    // Create a FEN string from the current position
    std::string toFEN();

    // Clears the board
    void clearBoard();

    // Print out representation of board
    void print();

    // Return 8x8 board
    std::vector<std::vector<Square> > getBoard();

    // Overloading access operator [] for integer indexing
    std::vector<Square>& operator[](int idx);

    Square& getSquare(std::tuple<int, int> loc);

    void makeMove(Move move);

    // Getters for gameplay
    bool getWhiteToPlay();
    int getHalfMove();
    int getMoveNumber();
    std::string getCastlingRights();
    std::string getEnPassantTargets();

    /*
    Generates all possible moves on the board for the color to play.
    Does not yet account for checks, pins, etc. 
    */
    std::vector<Move> generateMoves();



};

#endif