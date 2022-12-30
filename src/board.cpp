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

void Board::clearBoard() {
    for (int i = 0; i < 8; i++) {
        
        for (int j = 0; j < 8; j++) {
            board[i][j] = Square(i, j, nullptr);
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

void Board::makeMove(Move move) {
    whiteToPlay = !whiteToPlay;
}

bool Board::getWhiteToPlay() {
    return whiteToPlay;
}

Square& Board::getSquare(std::tuple<int, int> loc) {
    return board[std::get<0>(loc)][std::get<1>(loc)];
}

/*
This method is from the Queen class and is here as Board is forward declared in BasePiece
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
This method is from the King class and is here as Board is forward declared in BasePiece
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
        }  
    }
    return moves;
}

/*
This method is from the Rook class and is here as Board is forward declared in BasePiece
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

/*
This method is from the Bishop class and is here as Board is forward declared in BasePiece
*/
std::vector<Move> Bishop::getValidMoves(Board* board) {
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
This method is from the Knight class and is here as Board is forward declared in BasePiece
*/
std::vector<Move> Knight::getValidMoves(Board* board) {
    std::vector<Move> moves;

    // Iterate over directions looking for valid moves
    for (std::tuple<int, int> dir : directions) {
        for (int i = 1; i < 2; i++) {

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
            }         
        }
    }
    return moves;
}


std::vector<Move> Pawn::getValidMoves(Board* board) {
    std::vector<Move> moves;

    // Pawns can only move up board if white and down board if black
    int moveAmount = (board->getWhiteToPlay()) ? -1 : 1;
    int startRow = (board->getWhiteToPlay()) ? 6 : 1;
    char enemyColor = (board->getWhiteToPlay()) ? 'b' : 'w';

    // Pawns can only move forward
    if (std::get<0>(position) + moveAmount <= 7 && std::get<0>(position) + moveAmount >= 0) {
        // Square infront of pawn must be empty to move forward
        if (board[0][std::get<0>(position) + moveAmount][std::get<1>(position)].getPiece() == nullptr) {
            // Tuple of the ending square's position
            std::tuple<int, int> end = std::make_tuple(std::get<0>(position) + moveAmount, std::get<1>(position));
            Move move(position, end, this, board[0][std::get<0>(end)][std::get<1>(end)].getPiece());
            moves.push_back(move);

            // Pawns can move forward two squares if pawn has not moved yet
            if (std::get<0>(position) == startRow && board[0][std::get<0>(position) + (2 * moveAmount)][std::get<1>(position)].getPiece() == nullptr) {
                std::tuple<int, int> endSq = std::make_tuple(std::get<0>(position) + (2 * moveAmount), std::get<1>(position));
                Move twoSquarePawnMove(position, endSq, this, board[0][std::get<0>(position) + (2 * moveAmount)][std::get<1>(position)].getPiece());
                moves.push_back(twoSquarePawnMove);
            }
        }   

        // Pawns can only capture opposing pieces diagonally

        // Capture to left
        if (std::get<1>(position) - 1 >= 0) {
            if (board[0][std::get<0>(position) + moveAmount][std::get<1>(position) - 1].getPiece() != nullptr && board[0][std::get<0>(position) + moveAmount][std::get<1>(position) - 1].getPiece()->getID()[0] == enemyColor) {
                std::tuple<int, int> end = std::make_tuple(std::get<0>(position) + moveAmount, std::get<1>(position) - 1);
                Move leftCapture(position, end, this, board[0][std::get<0>(position) + moveAmount][std::get<1>(position) - 1].getPiece());
                moves.push_back(leftCapture);
            }
        }   

        // Capture to right
        if (std::get<1>(position) + 1 <= 7) {
            if (board[0][std::get<0>(position) + moveAmount][std::get<1>(position) + 1].getPiece() != nullptr && board[0][std::get<0>(position) + moveAmount][std::get<1>(position) + 1].getPiece()->getID()[0] == enemyColor) {
                std::tuple<int, int> end = std::make_tuple(std::get<0>(position) + moveAmount, std::get<1>(position) + 1);
                Move rightCapture(position, end, this, board[0][std::get<0>(position) + moveAmount][std::get<1>(position) + 1].getPiece());
                moves.push_back(rightCapture);     
            }      
        }   
    }


    return moves;
}