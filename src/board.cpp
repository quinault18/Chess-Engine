#include "board.h"

Board::Board() {
    // Initializing squares
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
                if (board[rank][file].getPiece()->getID() == "wK") {
                    whiteKingLocation = board[rank][file].getPiece()->getPosition();
                }
                if (board[rank][file].getPiece()->getID() == "bK") {
                    blackKingLocation = board[rank][file].getPiece()->getPosition();
                }
                file++;
            }
        }
    }
}

std::string Board::toFEN() {
    std::string fen;
    // Iterate over the ranks of the board
    for (int rank = 0; rank < board.size(); rank++) {

        // Number of empty squares before another piece
        int emptyCount = 0;

        // Iterate over the files of the rank
        for (int file = 0; file < board[rank].size(); file++) {
            // Increment emptyCount if no piece at square
            if (board[rank][file].getPiece() == nullptr) {
                emptyCount++;
            }
            // Add piece type to string. White pieces use capital letters, black pieces use lowercase letters
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
        // Ranks are denoted with a '/'
        if (rank < 7) {
            fen += '/';
        }
    }

    // Create the rest of the FEN string - active color, castling rights, en passant target, half move and move number
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

bool Board::operator==(const Board& other){
    Board o = other;
    return toFEN() == o.toFEN();
}

bool Board::operator!=(const Board& other){
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

    // increment move number when black makes a move
    if (!whiteToPlay) {
        moveNumber++;
    }

    // Change active color
    whiteToPlay = !whiteToPlay;

    // Half move count
    if (move.pieceMoved->getID()[0] != 'p' || move.pieceCaptured == nullptr) {
        halfMove++;
    }
    else {
        halfMove = 0;
    }
    
    // Castling
    if (move.isCastleMove) {

        // Kingside castle
        if (std::get<1>(move.end) > std::get<1>(move.start)) {
            // Black
            if (std::get<0>(move.start) == 0) {
                board[0][5].setPiece(board[0][7].getPiece());
                board[0][7].setPiece(nullptr);
                castlingRights.blackKingSide = false;
                castlingRights.blackQueenSide = false;
            }
            // White
            else {
                board[7][5].setPiece(board[7][7].getPiece());
                board[7][7].setPiece(nullptr);
                castlingRights.whiteKingSide = false;
                castlingRights.whiteQueenSide = false;
            }
        }
        else {
            // Black
            if (std::get<0>(move.start) == 0) {
                board[0][3].setPiece(board[0][0].getPiece());
                board[0][0].setPiece(nullptr);
                castlingRights.blackKingSide = false;
                castlingRights.blackQueenSide = false;
            }
            // White
            else {
                board[7][3].setPiece(board[7][0].getPiece());
                board[7][0].setPiece(nullptr);
                castlingRights.whiteKingSide = false;
                castlingRights.whiteQueenSide = false;
            }
        }
    }

    // Updating king locations
    if (move.pieceMoved->getID() == "wK") {
        whiteKingLocation = move.end;
    }
    else if (move.pieceMoved->getID() == "bK") {
        blackKingLocation = move.end;
    }
}

std::tuple<bool, std::vector<Pin>, std::vector<Check> > Board::getPinsAndChecks() {
    // Initialize vectors for pins, checks, and boolean value for inCheck
    bool inCheck = false;
    std::vector<Pin> pins;
    std::vector<Check> checks;

    char enemyColor = (whiteToPlay) ? 'b' : 'w';
    char allyColor = (whiteToPlay) ? 'w' : 'b';

    int startRow = (whiteToPlay) ? std::get<0>(whiteKingLocation) : std::get<0>(blackKingLocation);
    int startCol = (whiteToPlay) ? std::get<1>(whiteKingLocation) : std::get<1>(blackKingLocation);

    // Directions of possible pins and checks, excluding knights
    std::vector<std::tuple<int, int> > directions;
    // diretions for queens & bishops
    directions.push_back(std::make_tuple(1, 1));
    directions.push_back(std::make_tuple(1, -1));
    directions.push_back(std::make_tuple(-1, 1));
    directions.push_back(std::make_tuple(-1, -1));
    // directions for queens & rooks
    directions.push_back(std::make_tuple(1, 0));
    directions.push_back(std::make_tuple(0, 1));
    directions.push_back(std::make_tuple(-1, 0));
    directions.push_back(std::make_tuple(0, -1));

    // Iterate over directions for bishops, rooks, queens, and pawns
    for (int j = 0; j < directions.size(); j++) {

        std::tuple<int, int> dir = directions[j];
        std::vector<int> possiblePin;

        // Setup possible pin - can not be on squares (-1, -1) and is used for error checking
        Pin pin(-1, -1, -1, -1);

        // Radiate outward from current king position
        for (int i = 1; i < 8; i++) {

            // Square an attacking piece could be
            int endRow = startRow + std::get<0>(dir) * i;
            int endCol = startCol + std::get<1>(dir) * i;

            // Bounds checking
            if (0 <= endRow && endRow <= 7 && 0 <= endCol && endCol <= 7) {
                BasePiece* endPiece = board[endRow][endCol].getPiece();

                // If square is empty, move to next square in progression
                if (endPiece == nullptr) {
                    continue;
                }
                // If endPiece is opposite color and not a King, create a pin on that square as this piece could be attacking king
                else if (endPiece->getID()[0] == allyColor && endPiece->getID() != "K") {
                    if (possiblePin.size() == 0) {
                        pin = Pin(endRow, endCol, std::get<0>(dir), std::get<1>(dir));
                    }
                    else {
                        break;
                    }
                }
                // If piece is opposite color, check if it is directly checking king or is pinning another piece
                else if (endPiece->getID()[0] == enemyColor) {
                    char enemyType = endPiece->getID()[1];

                    /*
                    The directions vector is setup such that the first 4 elements are the directions bishops and queens can move in.
                    The last 4 elements are the directions queens and rooks can move in. 
                    This if statement checks the type of piece is compatible with the current direction.
                    */
                    if ((0 <= j && j <= 3 && enemyType == 'B') || 
                    (i == 1 && enemyType == 'p' && (enemyColor == 'w' && 0 <= i && i <= 1) || (enemyColor == 'b' && 2 <= j && j <= 3)) || 
                    (enemyType == 'Q') || (i == 1 && enemyType == 'K') ||
                    (4 <= j && j <= 7 && enemyType == 'R')) {

                        // If pin is not possible, that means endPiece is checking the king
                        if (pin.endRow == -1) {
                            inCheck = true;
                            Check check(endRow, endCol, std::get<0>(dir), std::get<1>(dir));
                            checks.push_back(check);
                            break;
                        }
                        // If the pin has been assigned a real value, there is a pin
                        else {
                            pins.push_back(pin);
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
    }

    // Knights move in an 'L' pattern and do not follow same rules for algorithm above
    // Knights also can not pin another piece
    std::vector<std::tuple<int, int> > knightDirections;
    knightDirections.push_back(std::make_tuple(2, 1));
    knightDirections.push_back(std::make_tuple(1, 2));
    knightDirections.push_back(std::make_tuple(-1, 2));
    knightDirections.push_back(std::make_tuple(-2, 1));
    knightDirections.push_back(std::make_tuple(-2, -1));
    knightDirections.push_back(std::make_tuple(-1, -2));
    knightDirections.push_back(std::make_tuple(1, -2));
    knightDirections.push_back(std::make_tuple(2, -1));

    for (std::tuple<int, int> move : knightDirections) {
        int endRow = startRow + std::get<0>(move);
        int endCol = startCol + std::get<1>(move);
        
        // Bounds checking
        if (0 <= endRow && endRow <= 7 && 0 <= endCol && endCol <= 7) {
            BasePiece* endPiece = board[endRow][endCol].getPiece();
            // Continue if this square is empty
            if (endPiece == nullptr) {
                continue;
            }
            // If the piece is a knight, the knight is checking the king as knights can not pin pieces.
            if (endPiece->getID()[0] == enemyColor && endPiece->getID()[1] == 'N') {
                inCheck = true;
                checks.push_back(Check(endRow, endCol, std::get<0>(move), std::get<1>(move)));
            }
        }
    }

    std::tuple<bool, std::vector<Pin>, std::vector<Check> > pinsAndChecks = std::make_tuple(inCheck, pins, checks);
    return pinsAndChecks;
}



bool Board::squareUnderAttack(Square& square) {
    // Change turns and get opposing color moves
    whiteToPlay = !whiteToPlay;
    std::vector<Move> opponentMoves = getAttackingMoves();
    whiteToPlay = !whiteToPlay;

    // Loop through moves and see if a move ends on that square
    for (Move move : opponentMoves) {
        // Squares pawns land on are not "under attack" if they are not diagonal
        if (move.pieceMoved->getID()[1] != 'p') {
            if (move.end == square.getLocation()) {
                return true;
            }
        }
        else {
            if (std::get<1>(move.start) != std::get<1>(move.end)) {
                if (move.end == square.getLocation()) {
                    return true;
                }
            }
        }
    }
    return false;
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

std::vector<Move> Board::getAttackingMoves() {
    std::vector<Move> moves;
    char enemyColor = (getWhiteToPlay()) ? 'b' : 'w';

    for (std::vector<Square> rank : board) {
        for (Square square : rank) {
            if (square.getPiece() != nullptr && square.getPiece()->getID()[0] != enemyColor && square.getPiece()->getID()[1] == 'p') {
                std::vector<Move> pieceMoves = square.getPiece()->getAttackingMoves(this);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
            else if (square.getPiece() != nullptr && square.getPiece()->getID()[0] != enemyColor && square.getPiece()->getID()[1] != 'p') {
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

std::vector<Move> Queen::getAttackingMoves(Board* board) {
    return getValidMoves(board);
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

    // Kings can also castle kingside and queenside
    std::vector<Move> castlingMoves = getCastlingMoves(board);
    moves.insert(moves.end(), castlingMoves.begin(), castlingMoves.end());
    return moves;
}

std::vector<Move> King::getAttackingMoves(Board* board) {
    return getValidMoves(board);
}

std::vector<Move> King::getCastlingMoves(Board* board) {
    std::vector<Move> castlingMoves;

    // If white is to play, get king and queenside castling moves, if possible
    if (board->getWhiteToPlay()) {
        if (board->getCastlingRights().whiteKingSide) {
            std::vector<Move> kingSideCastle = getKingSideCastlingMoves(board);
            castlingMoves.insert(castlingMoves.end(), kingSideCastle.begin(), kingSideCastle.end());
        }
        if (board->getCastlingRights().whiteQueenSide) {
            std::vector<Move> queenSideCastle = getQueenSideCastlingMoves(board);
            castlingMoves.insert(castlingMoves.end(), queenSideCastle.begin(), queenSideCastle.end());
        }
    }
    // If black is to play, get king and queenside castling moves, if possible
    else {
        if (board->getCastlingRights().blackKingSide) {
            std::vector<Move> kingSideCastle = getKingSideCastlingMoves(board);
            castlingMoves.insert(castlingMoves.end(), kingSideCastle.begin(), kingSideCastle.end());
        }
        if (board->getCastlingRights().blackQueenSide) {
            std::vector<Move> queenSideCastle = getQueenSideCastlingMoves(board);
            castlingMoves.insert(castlingMoves.end(), queenSideCastle.begin(), queenSideCastle.end());
        }
    }

    return castlingMoves;
}

std::vector<Move> King::getKingSideCastlingMoves(Board* board) {
    std::vector<Move> kingSideCastleMoves;
    int kingRank = std::get<0>(position);
    int kingFile = std::get<1>(position);

    // To castle kingside, the bishop's and knight's starting square on the kingside must be empty and not under attack
    if (board[0][kingRank][kingFile + 1].getPiece() == nullptr && board[0][kingRank][kingFile + 2].getPiece() == nullptr) {
        if (!board->squareUnderAttack(board[0][kingRank][kingFile + 1]) && !board->squareUnderAttack(board[0][kingRank][kingFile + 2])) {
            std::tuple<int, int> kingEndSquare = std::make_tuple(kingRank, kingFile + 2);
            Move kingSideCastleMove(position, kingEndSquare, this, board[0].getSquare(kingEndSquare).getPiece(), true);
            kingSideCastleMoves.push_back(kingSideCastleMove);
        }
    }

    return kingSideCastleMoves;
}

std::vector<Move> King::getQueenSideCastlingMoves(Board* board) {
    std::vector<Move> queenSideCastleMoves;
    int kingRank = std::get<0>(position);
    int kingFile = std::get<1>(position);

    // To castle queenside, the queen's, bishop's, and knight's starting square on the queenside must be empty and not under attack
    if (board[0][kingRank][kingFile - 1].getPiece() == nullptr && board[0][kingRank][kingFile - 2].getPiece() == nullptr && board[0][kingRank][kingFile - 3].getPiece() == nullptr) {
        if (!board->squareUnderAttack(board[0][kingRank][kingFile - 1]) && !board->squareUnderAttack(board[0][kingRank][kingFile - 2]) && !board->squareUnderAttack(board[0][kingRank][kingFile - 3])) {
            std::tuple<int, int> kingEndSquare = std::make_tuple(kingRank, kingFile - 2);
            Move queenSideCastleMove(position, kingEndSquare, this, board[0].getSquare(kingEndSquare).getPiece(), true);
            queenSideCastleMoves.push_back(queenSideCastleMove);
        }
    }

    return queenSideCastleMoves;
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

std::vector<Move> Rook::getAttackingMoves(Board* board) {
    return getValidMoves(board);
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

std::vector<Move> Bishop::getAttackingMoves(Board* board) {
    return getValidMoves(board);
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

std::vector<Move> Knight::getAttackingMoves(Board* board) {
    return getValidMoves(board);
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

std::vector<Move> Pawn::getAttackingMoves(Board* board) {
    std::vector<Move> moves;

    // Pawns can only move up board if white and down board if black
    int moveAmount = (board->getWhiteToPlay()) ? -1 : 1;
    int startRow = (board->getWhiteToPlay()) ? 6 : 1;
    char enemyColor = (board->getWhiteToPlay()) ? 'b' : 'w';

    if (std::get<0>(position) + moveAmount <= 7 && std::get<0>(position) + moveAmount >= 0) {
        // Pawns can only capture opposing pieces diagonally

        // Capture to left
        if (std::get<1>(position) - 1 >= 0) {
            std::tuple<int, int> end = std::make_tuple(std::get<0>(position) + moveAmount, std::get<1>(position) - 1);
            Move leftCapture(position, end, this, board[0][std::get<0>(position) + moveAmount][std::get<1>(position) - 1].getPiece());
            moves.push_back(leftCapture);
        }   

        // Capture to right
        if (std::get<1>(position) + 1 <= 7) {
            std::tuple<int, int> end = std::make_tuple(std::get<0>(position) + moveAmount, std::get<1>(position) + 1);
            Move rightCapture(position, end, this, board[0][std::get<0>(position) + moveAmount][std::get<1>(position) + 1].getPiece());
            moves.push_back(rightCapture);     
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
        if (m.isCastleMove) {
            if (std::get<1>(m.start) > file) {
                os << "O-O";
            }
            else {
                os << "O-O-O";
            }
            return os;
        }
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