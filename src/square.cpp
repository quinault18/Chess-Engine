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
    piece = pieceToSet;
}