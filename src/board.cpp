#include "board.h"

Board::Board() {

    // This is the starting position of a standard game of chess
    std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    loadFromFEN(startingPosition);
}

Board::Board(std::string fen) {

    // Then load the pieces based on the FEN
    loadFromFEN(fen);
}

void Board::initBoard() {
    // 8x8 grid on squares
    for (int i = 0; i < 8; i++) {
        std::vector<Square> rank;
        for (int j = 0; j < 8; j++) {
            rank.push_back(Square(i, j, nullptr));
        }
        board.push_back(rank);
    }
}


void Board::loadFromFEN(std::string fen) {

    // First load the squares
    initBoard();
    // Break FEN string into components
    std::vector<std::string> parsedFEN = parseFEN(fen);

    // Turn to play
    whiteToPlay = (parsedFEN[1] == "w") ? true : false;

    int rank = 0;
    int file = 0;

    std::string position = parsedFEN[0];
    for (char c : position) {

        // Ranks are delineated by a '/' symbol
        if (c == '/') {
            rank = rank + 1;
            file = 0;
        }
        else {
            // Skip number of empty squares
            if (isdigit(c)) 
                file = file + int(c) - '0';
            else {

                // Determine color of piece
                char color = (isupper(c)) ? 'w': 'b';
                char id;

                // Uppercase characters mean white minor and major pieces
                if (isupper(c)) {
                    if (c != 'P') 
                        id = c;
                    // White pawns are represented with an uppercase 'P'
                    else
                        id = tolower(c);
                }

                // Lowercase characters mean black minor and major pieces
                else {
                    if (c != 'p')
                        id = toupper(c);
                    // Black pawns are represented with a lowercase 'p'
                    else 
                        id = c;
                }

                // Adding piece to board and moving to the next file in this rank
                std::tuple<int, int> position = std::make_tuple(rank, file);
                board[rank][file].setPiece(new BasePiece(std::string(1, color) + id, position));
                file++;
            }
        }
    }
}

std::vector<std::string> Board::parseFEN(std::string fen) {

    // FEN strings are split by a space, add parsed segments to vector
    std::vector<std::string> parsed;
    int index = 0;
    int length = 0;
    for (char c : fen) {
        if (c != ' ') 
            length++;
        else {        
            parsed.push_back(fen.substr(index, length));
            index = index + length + 1;
            length = 0;         
        }
    }

    parsed.push_back(fen.substr(index, length));
    return parsed;
}

std::vector<std::vector<Square> > Board::getBoard() {
return board;
}

std::vector<Square>& Board::operator[](int idx) {
    return board[idx];
}

void Board::print() {

    // Iterate over board and print out piece id, '--' if empty
    for (int i = 0; i < board.size(); i++) {
        std::string rank = "";
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j].getPiece())
                rank = rank + board[i][j].getPiece()->getID() + " ";
            else
                rank = rank + "--" + " ";
        }
        std::cout << rank << std::endl;
    }
}

bool Board::getWhiteToPlay() {
    return whiteToPlay;
}

Square& Board::getSquare(std::tuple<int, int> loc) {
    return board[std::get<0>(loc)][std::get<1>(loc)];
}

/*
This method is from the Queen class and is here as Board is forward declared in Queen.
*/
std::vector<Move> Queen::getValidMoves(Board* board) {
    std::vector<Move> moves;

    // Iterate over directions looking for valid moves
    for (std::tuple<int, int> dir : directions) {
        for (int i = 1; i < 8; i++) {

            // Ending coordinates of move
            int endRow = std::get<0>(position) + std::get<0>(dir) * i;
            int endCol = std::get<1>(position) + std::get<1>(dir) * i;
            std::tuple<int, int> end = std::make_tuple(endRow, endCol);

            // Error checking bounds making sure move ends on board
            if (0 <= endRow && endRow < 8 && 0 <= endCol && endCol < 8) {

                // Checking if (endRow, endCol) is empty
                if (board[0][endRow][endCol].getPiece() == nullptr) {
                    Move move(position, end, this, board[0][endRow][endCol].getPiece());
                    moves.push_back(move);
                }

                // If not empty, piece must be other color. Can not move beyond that piece
                else if (board[0][endRow][endCol].getPiece()->getID()[0] != this->getID()[0]) {
                    Move move(position, end, this, board[0][endRow][endCol].getPiece());
                    moves.push_back(move);
                    break;
                }

                // If piece is same color, stop looking for moves in this direction
                else {
                    break;
                }
            }         
        }
    }
    return moves;
}

/*
This method is from the King class and is here as Board is forward declared in King
*/
std::vector<Move> King::getValidMoves(Board* board) {
    std::vector<Move> moves;

    // Iterate over directions looking for valid moves
    for (std::tuple<int, int> dir : directions) {

        // Ending coordinates of move
        int endRow = std::get<0>(position) + std::get<0>(dir);
        int endCol = std::get<1>(position) + std::get<1>(dir);
        std::tuple<int, int> end = std::make_tuple(endRow, endCol);

        // Error checking bounds making sure move ends on board
        if (0 <= endRow && endRow < 8 && 0 <= endCol && endCol < 8) {

            // Checking if (endRow, endCol) is empty
            if (board[0][endRow][endCol].getPiece() == nullptr) {
                Move move(position, end, this, board[0][endRow][endCol].getPiece());
                moves.push_back(move);
            }

            // If not empty, piece must be other color. Can not move beyond that piece
            else if (board[0][endRow][endCol].getPiece()->getID()[0] != this->getID()[0]) {
                Move move(position, end, this, board[0][endRow][endCol].getPiece());
                moves.push_back(move);
                break;
            }

            // If piece is same color, stop looking for moves in this direction
            else {
                break;
            }
        }  
    }

    return moves;
}

/*
This method is from the Rook class and is here as Board is forward declared in Rook
*/
std::vector<Move> Rook::getValidMoves(Board* board) {
    std::vector<Move> moves;
    // Iterate over directions looking for valid moves
    for (std::tuple<int, int> dir : directions) {
        for (int i = 1; i < 8; i++) {

            // Ending coordinates of move
            int endRow = std::get<0>(position) + std::get<0>(dir) * i;
            int endCol = std::get<1>(position) + std::get<1>(dir) * i;
            std::tuple<int, int> end = std::make_tuple(endRow, endCol);

            // Error checking bounds making sure move ends on board
            if (0 <= endRow && endRow < 8 && 0 <= endCol && endCol < 8) {

                // Checking if (endRow, endCol) is empty
                if (board[0][endRow][endCol].getPiece() == nullptr) {
                    Move move(position, end, this, board[0][endRow][endCol].getPiece());
                    moves.push_back(move);
                }

                // If not empty, piece must be other color. Can not move beyond that piece
                else if (board[0][endRow][endCol].getPiece()->getID()[0] != this->getID()[0]) {
                    Move move(position, end, this, board[0][endRow][endCol].getPiece());
                    moves.push_back(move);
                    break;
                }

                // If piece is same color, stop looking for moves in this direction
                else {
                    break;
                }
            }         
        }
    }
    return moves;

}