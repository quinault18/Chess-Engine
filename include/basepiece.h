#ifndef BASEPIECE_H
#define BASEPIECE_H

#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <iostream>

#include "move.h"


class Board;

class BasePiece {
    private:
        std::string id;
    
    protected:

        // List of the directions a piece can move. This is used to find the valid moves
        std::vector<std::tuple<int, int> > directions;

        // The current position of this piece. This is set when the piece is placed 
        // on the board and is updated when a move is made on the board with this piece
        std::tuple<int, int> position;

    public: 

        /*
        The id of the piece is the color (white of black, 'w' or 'b') and the ID of the piece.
        King -> 'K'
        Queen -> 'Q'
        Rook -> 'R'
        Bishop -> 'B'
        Knight -> "N"
        Pawn -> 'p'
        */
        BasePiece(std::string id);

        /*
        The position of the piece is the (rank, file) tuple of this piece on the board. This is updated when
        a move is made with this piece.
        */
        BasePiece(std::string id, std::tuple<int, int> pos);
        virtual ~BasePiece() = default;

        BasePiece(const BasePiece& other);

        BasePiece& operator=(BasePiece other);

        /*
        Returns the id of this piece
        */
        std::string getID();

        /*
        Returns the position of this piece
        */
        std::tuple<int, int> getPosition();

        /*
        Method for generating the valid moves a piece has. To be overriden by each child class.
        */
        virtual std::vector<Move> getValidMoves(Board* board);

    
};

#endif