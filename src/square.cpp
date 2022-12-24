#include "square.h"

Square::Square(int rank, int file, BasePiece* piece) : piece(piece) {
    location = std::make_tuple(rank, file);
}

std::tuple<int, int> Square::getLocation() {
    return location;
}

BasePiece* Square::getPiece() {
    return piece;
}

void Square::setPiece(BasePiece* pieceToSet) {
    std::string id = pieceToSet->getID();
    switch (id[1]) {
        case 'Q': 
            piece = new Queen(id);
            break;
        case 'K':
            piece = new King(id);
            break;
        case 'R':
            piece = new Rook(id);
            break;
        case 'N':
            piece = new Knight(id);
            break;
        case 'B':  
            piece = new Bishop(id);
            break;
        case 'p':  
            piece = new Pawn(id);
            break;
        default:
            break;
    }
}