#include "square.h"

Square::Square(int rank, int file, BasePiece* piece) : piece(piece) {
    location = std::make_tuple(rank, file);
}


Square::~Square() {
    if (!piece) {
        delete piece;
    }
}


Square::Square(const Square& other) {
    location = other.location;
    piece = other.piece;
}

Square& Square::operator=(Square other) {
    std::swap(location, other.location);
    std::swap(piece, other.piece);

    return *this;
}

std::tuple<int, int> Square::getLocation() {
    return location;
}

BasePiece* Square::getPiece() {
    return piece;
}

void Square::setPiece(BasePiece* pieceToSet) {

    std::string id = pieceToSet->getID();
    std::tuple<int, int> position = pieceToSet->getPosition();
    switch (id[1]) {
        case 'Q': 
            piece = new Queen(id, position);
            break;
        case 'K':
            piece = new King(id, position);
            break;
        case 'R':
            piece = new Rook(id, position);
            break;
        case 'N':
            piece = new Knight(id, position);
            break;
        case 'B':  
            piece = new Bishop(id, position);
            break;
        case 'p':  
            piece = new Pawn(id, position);
            break;
        default:
            break;
    }
}