#ifndef MOVE_H
#define MOVE_H


#include <tuple>
#include <map>
#include <string>
// Forward declaration of BasePiece 
class BasePiece;

class Move {

    private:
        int id;

        // Move id is used to generate a unique identifier for each move
        int generateMoveID(std::tuple<int, int> t1, std::tuple<int, int> t2);

    public:  
        // A move on the chessboard has a starting and ending position, and a piece that moved.
        // If the piece that moved captured another piece, that is stored in the pieceCaptured variable
        Move(std::tuple<int, int> start, std::tuple<int, int> end, BasePiece* pieceMoved, BasePiece* pieceCaptured);

        BasePiece* pieceMoved;
        BasePiece* pieceCaptured;

        // Starting and ending positions of the piece moved on the chessboard
        std::tuple<int, int> start;
        std::tuple<int, int> end;
        
        // Maps for generating algebraic chess notation
        std::map<int, int> rowsToRanks;
        std::map<int, char> colsToFiles;

        int getMoveID();

        std::string getRankFile(int row, int col);

};

#endif