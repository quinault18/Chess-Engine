#ifndef BOARD_H
#define BOARD_H

#include "castlingRights.h"
#include "square.h"
#include <iostream>
#include <vector>


struct Pin {
    public:
        int endRow;
        int endCol;
        int dirRow;
        int dirCol;

        Pin(int eRow, int eCol, int dRow, int dCol) : endRow(eRow), endCol(eCol), dirRow(dRow), dirCol(dCol) {}
};

struct Check {
    public: 
        int endRow;
        int endCol;
        int dirRow;
        int dirCol;

        Check(int eRow, int eCol, int dRow, int dCol) : endRow(eRow), endCol(eCol), dirRow(dRow), dirCol(dCol) {}
};


class Board {

private:

    // 8x8 vector of Squares to represent the board
    std::vector<std::vector<Square> > board;

    // Active color
    bool whiteToPlay;

    // Castling rights
    CastlingRights castlingRights;

    // En Passant targets
    std::string enPassantTargets;

    // Halfmove and full move count
    int halfMove;
    int moveNumber;

    // Helper method for loading the board from a FEN string
    std::vector<std::string> parseFEN(std::string fen);

    // Helper method for initializing the board
    void initBoard();

    // Values for white and black king location
    std::tuple<int, int> whiteKingLocation;
    std::tuple<int, int> blackKingLocation;



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
    Board& operator=(Board other);

    /*
    Equality operator overloading
    */
    bool operator==(const Board& other);
    bool operator!=(const Board& other);
    
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

    // Access a square via a tuple rather than the access operator[] 
    Square& getSquare(std::tuple<int, int> loc);

    /*
    Method to make a move on the board.
    */
    void makeMove(Move move);

   /*
   Determine if square is under attack by enemy piece
   */
    bool squareUnderAttack(Square& square);

    // Getters for gameplay
    bool getWhiteToPlay();
    int getHalfMove();
    int getMoveNumber();
    CastlingRights getCastlingRights();
    std::string getEnPassantTargets();

    /*
    Generates all attacking moves. For pawns, this includes diagonal attacking moves
    that do not attack antything.
    */
    std::vector<Move> getAttackingMoves();
    /*
    Generates all valid moves on the board for the color to play.
    Does not yet account for checks, pins, etc. 
    */
    std::vector<Move> generateMoves();

    /*
    Gen pins and checks
    */
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > getPinsAndChecks();

};



#endif