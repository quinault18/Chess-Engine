#include "castlingRights.h"


CastlingRights::CastlingRights() {
    whiteKingSide = false;
    whiteQueenSide = false;
    blackKingSide = false;
    blackQueenSide = false; 
}

CastlingRights::CastlingRights(bool wks, bool wqs, bool bks, bool bqs) :
    whiteKingSide(wks), whiteQueenSide(wqs), blackKingSide(bks), blackQueenSide(bqs) {}

CastlingRights::CastlingRights(std::string rights) {

    whiteKingSide = false;
    whiteQueenSide = false;
    blackKingSide = false;
    blackQueenSide = false;

    if (rights.find('K') != std::string::npos) {
        whiteKingSide = true;
    }
    if (rights.find('Q') != std::string::npos) {
    whiteQueenSide = true;
    }
    if (rights.find('k') != std::string::npos) {
    blackKingSide = true;
    }
    if (rights.find('q') != std::string::npos) {
    blackQueenSide = true;
    }
}
CastlingRights::~CastlingRights() {}

CastlingRights::CastlingRights(const CastlingRights& other) {
    whiteKingSide = other.whiteKingSide;
    whiteQueenSide = other.whiteQueenSide;
    blackKingSide = other.blackKingSide;
    blackQueenSide = other.blackQueenSide;
}

CastlingRights& CastlingRights::operator=(CastlingRights other) {
    std::swap(whiteKingSide, other.whiteKingSide);
    std::swap(whiteQueenSide, other.whiteQueenSide);
    std::swap(blackKingSide, other.blackKingSide);
    std::swap(blackQueenSide, other.blackQueenSide);

    return *this;
}

std::string CastlingRights::toString() {
    std::string castlingRights;
    if (whiteKingSide)
        castlingRights += "K";
    if (whiteQueenSide)
        castlingRights += "Q";
    if (blackKingSide) 
        castlingRights += "k";
    if (blackQueenSide)
        castlingRights += "q";
    if (!whiteKingSide && !whiteQueenSide && !blackKingSide && !blackQueenSide)
        castlingRights += "-";
    
    return castlingRights;
}