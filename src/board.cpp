#include "board.h"

Board::Board() {

    initBoard();

    // This is the starting position of a standard game of chess
    std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    loadFromFEN(startingPosition);
}

Board::Board(std::string fen) {

    initBoard();
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

Board::~Board() {}


Board::Board(const Board& other) {
    board = other.board;
    whiteToPlay = other.whiteToPlay;
    castlingRights = other.castlingRights;
    enPassantTargets = other.enPassantTargets;
    halfMove = other.halfMove;
    moveNumber = other.moveNumber;
}

Board& Board::operator=(Board other) {
    std::swap(board, other.board);
    std::swap(whiteToPlay, other.whiteToPlay);
    std::swap(castlingRights, other.castlingRights);
    std::swap(enPassantTargets, other.enPassantTargets);
    std::swap(halfMove, other.halfMove);
    std::swap(moveNumber, other.moveNumber);

    return *this;
}

void Board::loadFromFEN(std::string fen) {

    // Break FEN string into components
    std::vector<std::string> parsedFEN = parseFEN(fen);

    // Turn to play
    whiteToPlay = (parsedFEN[1] == "w") ? true : false;

    // Castling rights, en passant targets, and move count
    CastlingRights cr(parsedFEN[2]);
    castlingRights = cr;
    enPassantTargets = parsedFEN[3];
    halfMove = std::stoi(parsedFEN[4]);
    moveNumber = std::stoi(parsedFEN[5]);

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
                board[rank][file].setPieceAtStart(new BasePiece(std::string(1, color) + id, position));
                file++;
            }
        }
    }
}

std::string Board::toFEN() {
    std::string fen;

    for (int rank = 0; rank < board.size(); rank++) {
        int emptyCount = 0;
        for (int file = 0; file < board[rank].size(); file++) {
            if (board[rank][file].getPiece() == nullptr) {
                emptyCount++;
            }
            else {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);       
                    emptyCount = 0;
                }
                std::string id = board[rank][file].getPiece()->getID();
                if (id[0] == 'w') {
                    fen += toupper(id[1]);
                }
                else {
                    fen += tolower(id[1]);
                }
            }
        }
        if (emptyCount > 0) {
            fen += std::to_string(emptyCount);
        }
        if (rank < 7) {
            fen += '/';
        }
    }

    fen += (getWhiteToPlay()) ? " w " : " b ";
    fen += castlingRights.toString();
    fen += " - ";
    fen += std::to_string(halfMove);
    fen += " " + std::to_string(moveNumber);

    return fen;
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

bool Board::operator==(const Board& other) {
    Board o = other;
    return toFEN() == o.toFEN();
}

bool Board::operator!=(const Board& other) {
    return !(*this == other);
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
    // Set end squre piece to moved piece
    getSquare(move.end).setPiece(move.pieceMoved);
    // Set position of moved piece to end square
    move.pieceMoved->setPosition(move.end);
    // Set start square piece to empty
    getSquare(move.start).setPiece(nullptr);
    whiteToPlay = !whiteToPlay;
}

bool Board::getWhiteToPlay() {
    return whiteToPlay;
}

int Board::getHalfMove() {
    return halfMove;
}

int Board::getMoveNumber() {
    return moveNumber;
}

CastlingRights Board::getCastlingRights() {
    return castlingRights;
}

std::string Board::getEnPassantTargets() {
    return enPassantTargets;
}

Square& Board::getSquare(std::tuple<int, int> loc) {
    return board[std::get<0>(loc)][std::get<1>(loc)];
}

std::vector<Move> Board::generateMoves() {
    std::vector<Move> moves;
    //Board boardCopy(this&);
    char enemyColor = (getWhiteToPlay()) ? 'b' : 'w';

    for (std::vector<Square> rank : board) {
        for (Square square : rank) {
            if (square.getPiece() != nullptr && square.getPiece()->getID()[0] != enemyColor) {
                std::vector<Move> pieceMoves = square.getPiece()->getValidMoves(this);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return moves;
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


std::ostream& operator<<(std::ostream& os, const Move& move) {
    Move m(move);
    char piece = move.pieceMoved->getID()[1];
    int rank = std::get<0>(m.end);
    int file = std::get<1>(m.end);
    std::string endingSquare = m.getRankFile(rank, file);

    // Pawn moves are denoted by the file and rank, not piece type
    if (piece == 'p') {
        // Pawn push
        if (std::get<1>(m.start) - std::get<1>(m.end) == 0) {
            os << m.getRankFile(rank, file);
        }
        else {
            os << m.getRankFile(std::get<0>(m.start), std::get<1>(m.start))[0] << 'x' << m.getRankFile(rank, file);
        }
    }
    else {
        // No Capture
        if (m.pieceCaptured == nullptr) {
            os << piece << m.getRankFile(rank, file);
        }
        else {
            os << piece << 'x' << m.getRankFile(rank, file);
        }
    }
    return os;

}