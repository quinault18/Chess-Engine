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

        

        /**
         * @brief Move id is used to generate a unique identifier for each move.
         * The move id is in the format as follows:
         *   Thousands place - t1[0]
         *   Hundreds place  - t1[1]
         *   Tens place      - t2[0]
         *   Ones place      - t2[1]
        */
        int generateMoveID(std::tuple<int, int> t1, std::tuple<int, int> t2);

    public:  
        /**
         * @brief Construct a new Move object
         * 
         * @param start - starting position of the move
         * @param end - ending position of the move
         * @param pieceMoved - pointer to the piece that was moved
         * @param pieceCaptured - pointer to the piece that was captured
         * @param isCastle - value representing if the move is a castling move
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

        /**
         * @brief Returns the move id of this move.
         * 
         * @return int - id of the move
        */
        int getMoveID();

        /** 
         * @brief Used for generating the algebraic chess notation of this move.
         * 
         * @return std::string - algebraic notation of this move
        */
        std::string getRankFile(int row, int col);

        /**
         * @brief Print the algebraic chess notation of this move
        */
        friend std::ostream& operator<<(std::ostream& os, const Move& move);

};

#endif