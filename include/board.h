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

    /**
     * @brief Helper method for loading the board from a FEN string. The 6 components of a FEN string are
     *  1. position
     *  2. Active color
     *  3. Castling rights
     *  4. En passant target square
     *  5. Half move number
     *  6. Move number
     * 
     * @param fen - FEN string of a chess position
     * @return std::vector<std::string> - parsed fen string
     */
    std::vector<std::string> parseFEN(std::string fen);

    /**
     * @brief Initialiizes the 64 squares on the chessboard.
     * 
     */
    void initBoard();

    // Values for white and black king location
    std::tuple<int, int> whiteKingLocation;
    std::tuple<int, int> blackKingLocation;

public:

    /**
     * @brief Default constructor - loads 8x8 board with the standard starting position of the pieces
     * 
    */
    Board();

    /**
     * @brief Construct a new Board objectIf a FEN string is passed, load the board with the passed string
     * 
     * @param fen - FEN string to be loaded 
     */
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

    /**
     * @brief Overloading access operator [] for integer indexing
     * 
     * @param idx - rank to get
     * @return std::vector<Square>& - gets the rank of idx
     */
    std::vector<Square>& operator[](int idx);
    
    // BOARD INITIALIZATION

    /**
     * @brief All chess positions have a valid FEN string. This string gives the current position of the pieces,
     * the castling rights, the en passant target square, the half move count, and the current move number. This method
     * loads the FEN string's position to the Board and sets up the correct game play values.
     * 
     * @param fen - FEN string to be loaded
     */
    void loadFromFEN(std::string fen);

    /**
     * @brief Creates a FEN string from the current position and game play values (castling, en passant target, half move and move number)
     * 
     * @return std::string - FEN string of the current position
     */
    std::string toFEN();

    /**
     * @brief Sets all squares to have an empty (nullptr) piece.
     * 
     */
    void clearBoard();

    /**
     * @brief Prints a visual representation of the current position on the board/
     * 
     */
    void print();

    /**
     * @brief Returns the 8x8 board vector of this position
     * 
     * @return std::vector<std::vector<Square> > - 8x8 array of the squares and corresponding pieces
     */
    std::vector<std::vector<Square> > getBoard();

    /**
     * @brief Get the Square object at loc. This is used in conjuction with the overloaded [] operator.
     * 
     * @param loc - tuple holding coordinates of desired Square
     * @return Square& - reference to Square at loc
     */
    Square& getSquare(std::tuple<int, int> loc);


    // GETTERS FOR GAMEPLAY //

    /**
     * @brief Getter for the current active color.
     * 
     * @return true - white is to play
     * @return false - black is to play
     */
    bool getWhiteToPlay();

    /**
     * @brief Get the half move count. This is a value that represents the number of turns that have been played
     * since a capture or a pawn move. Once this value reaches 50, the game is drawn.
     * 
     * @return int - moves since a pawn move or capture
     */
    int getHalfMove();

    /**
     * @brief Get the move number. Increments after black has played a move
     * 
     * @return int - current move number
     */
    int getMoveNumber();

    /**
     * @brief Get the current castling rights of this position. 
     * 
     * @return CastlingRights - current castling rights of this postion
     */
    CastlingRights getCastlingRights();

    /**
     * @brief Gets the en passant target square. If en passant is possible, this returns the square en passant can happen on.
     * For instance, if a white pawn is on e5 and black playes f5, en passant is possible on the f6 square 
     * 
     * @return std::string - possible en passant target
     */
    std::string getEnPassantTargets();

    // MOVE GENERATION METHODS //

    /**
     * @brief Generates all attacking moves. For pawns, this includes diagonal attacking moves
     * that do not attack antything. For all other pieces, it returns the possible moves for that piece. 
     * 
     * @return std::vector<Move> - moves that attack squares.
     */
    std::vector<Move> getAttackingMoves();

    /**
     * @brief Generates all valid moves on the board for the color to play.
     * Does not yet account for checks, pins, etc. 
     * 
     * @return std::vector<Move> - all possible moves in the current position
     */
    std::vector<Move> generateMoves();

    /**
     * @brief Finds all pins and checks in the current position. A pin is a piece that if moved would result in the 
     * same color's king being in check, which is illegal. A check is a piece that is directly attacking the opposing king.
     * 
     * @return std::tuple<bool, std::vector<Pin>, std::vector<Check> > The boolean value is true if the king is in check.
     *      The std::vector<Pin> is a vector of all pins in the current position
     *      The std::vector<Check> is a vector of all checks in the current position
     */
    std::tuple<bool, std::vector<Pin>, std::vector<Check> > getPinsAndChecks();

    /**
     * @brief Determines if a square is under attack by an enemy piece. If an enemy piece's move ends on this square,
     * the squre is under attack.
     * 
     * @param square - Square object that could be under attack
     * @return true - if the square is under attack
     * @return false - if the square is not under attack
     */
    bool squareUnderAttack(Square& square);

    /**
     * @brief Makes a move on the board. The Move object stores the starting and ending square as well as the piece moved and 
     * piece captured, if valid. May also contain if the move is a castling move or en passant move.
     * This method sets the starting square of the move empty, and sets the ending square of the move to the piece moved.
     * Has functionality of playing a castling move.
     * 
     * TODO - implement en passant moves
     * 
     * @param move - Move object to be played
     */
    void makeMove(Move move);

};



#endif