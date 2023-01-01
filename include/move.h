#ifndef MOVE_H
#define MOVE_H


#include <tuple>
#include <map>
#include <string>
#include <iostream>

// Forward declaration of BasePiece 
class BasePiece;

class Move {

    private:
        int id;

        

        /*
        Move id is used to generate a unique identifier for each move.
        The move id is in the format as follows:
            Thousands place - t1[0]
            Hundreds place  - t1[1]
            Tens place      - t2[0]
            Ones place      - t2[1]
        */
        int generateMoveID(std::tuple<int, int> t1, std::tuple<int, int> t2);

    public:  
        /* A move on the chessboard has a starting and ending position, and a piece that moved.
         If the piece that moved captured another piece, that is stored in the pieceCaptured variable
        */
        Move(std::tuple<int, int> start, std::tuple<int, int> end, BasePiece* pieceMoved, BasePiece* pieceCaptured = nullptr, bool isCastle = false);
       
        /*
        Rule of Three implementation
        */
       ~Move();
        Move(const Move& other);
        Move& operator=(Move other);

        /*
        Equality operator overloading 
        */
        bool operator==(const Move other) const;
        bool operator!=(const Move other) const;

        // Stores the piece that moved and the piece that was captured, if applicable
        BasePiece* pieceMoved;
        BasePiece* pieceCaptured;

        // Starting and ending positions of the piece moved on the chessboard
        std::tuple<int, int> start;
        std::tuple<int, int> end;

        // Castling and en passant rights
        bool isCastleMove;
        
        // Maps for generating algebraic chess notation
        std::map<int, int> rowsToRanks;
        std::map<int, char> colsToFiles;

        /*
        Returns the move id of this move.
        */
        int getMoveID();

        /*
        Used for generating the algebraic chess notation of this move.
        */
        std::string getRankFile(int row, int col);

        /*
        Print the algebraic chess notation of this move
        */
        friend std::ostream& operator<<(std::ostream& os, const Move& move);

};

#endif