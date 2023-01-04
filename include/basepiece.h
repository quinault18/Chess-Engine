#ifndef BASEPIECE_H
#define BASEPIECE_H

#include <vector>
#include <string>
#include <tuple>
#include <iostream>

#include "move.h"

// Forward declaration of the Board.
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

        /**
         * @brief The id of the piece is the color (white of black, 'w' or 'b') and the ID of the piece.
         * King -> 'K'
         * Queen -> 'Q'
         * Rook -> 'R'
         * Bishop -> 'B'
         * Knight -> "N"
         * Pawn -> 'p'
         * 
         * @param id - id of the piece
         */
        BasePiece(std::string id);

        /**
         * @brief The position of the piece is the (rank, file) tuple of this piece on the board. 
         * This is updated when a move is made with this piece.
         * 
         * @param id - id pos the piece
         * @param pos - starting position of the piece
         */
        BasePiece(std::string id, std::tuple<int, int> pos);

        /**
         * @brief Destroy the Base Piece object
         * 
         */
        virtual ~BasePiece() = default;

        /**
         * @brief Construct a new Base Piece object
         * 
         * @param other 
         */
        BasePiece(const BasePiece& other);

        /**
         * @brief Assignment operator override
         * 
         * @param other 
         * @return BasePiece& 
         */
        BasePiece& operator=(BasePiece other);

        /*
        Returns the id of this piece
        */
        std::string getID();

        /**
         * @brief Returns the position of this piece
         * 
         * @return std::tuple<int, int> - position of this piece
         */
        std::tuple<int, int> getPosition();

        /**
         * @brief Set the position of this piece
         * 
         * @param newPos - new position of the piece when a move is made
         */
       void setPosition(std::tuple<int, int> newPos);

        /**
         * @brief Method for generating the valid moves a piece has. To be overriden by each child class.
         * 
         * @param board - Board pointer
         * @return std::vector<Move> - list of all valid moves this piece has
         */
        virtual std::vector<Move> getValidMoves(Board* board);

        /**
         * @brief Method for generating all attacking moves a piece has. An attacking move is a move where a piece 
         * can be captured by this piece.
         * 
         * @param board - Board pointer
         * @return std::vector<Move> - list of the attacking moves this piece has 
         */
        virtual std::vector<Move> getAttackingMoves(Board* board);
    
};

#endif