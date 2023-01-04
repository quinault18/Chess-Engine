#include "move.h"

Move::Move(std::tuple<int, int> start, std::tuple<int, int> end, BasePiece* pieceMoved, BasePiece* pieceCaptured, bool isCastle) :
    start(start), end(end), pieceMoved(pieceMoved), pieceCaptured(pieceCaptured), isCastleMove(isCastle) {

    id = generateMoveID(start, end);

    // Populate rowsToRanks
    for (int i = 1; i <= 8; i++) {
        rowsToRanks.insert(std::pair<int, int>(8 - i, i));
    }

    // Populate colsToFiles
    std::string str = "abcdefgh";
    int i = 0;
    for (char c : str) {
        colsToFiles.insert(std::pair<int, char>(i, c));
        i++;
    }
}

Move::Move(const Move& other) {
    id = other.id;
    pieceMoved = other.pieceMoved;
    pieceCaptured = other.pieceCaptured;
    start = other.start;
    end = other.end;
    rowsToRanks = other.rowsToRanks;
    colsToFiles = other.colsToFiles;
    isCastleMove = other.isCastleMove;
}

Move& Move::operator=(Move other) {
    std::swap(id, other.id);
    std::swap(pieceMoved, other.pieceMoved);
    std::swap(pieceCaptured, other.pieceCaptured);
    std::swap(start, other.start);
    std::swap(end, other.end);
    std::swap(rowsToRanks, other.rowsToRanks);
    std::swap(colsToFiles, other.colsToFiles);
    std::swap(isCastleMove, other.isCastleMove);

    return *this;
}

Move::~Move() {
    if (!pieceMoved) {
        delete pieceMoved;
    }
    if (!pieceCaptured) {
        delete pieceCaptured;
    }
}

bool Move::operator==(const Move other) const {
    return id == other.id && pieceMoved == other.pieceMoved && pieceCaptured == other.pieceCaptured && start == other.start && end == other.end;
}

bool Move::operator!=(const Move other) const {
    return !(*this == other);
}


int Move::generateMoveID(std::tuple<int, int> t1, std::tuple<int, int> t2) {
    int thousand = std::get<0>(t1);
    int hundred = std::get<1>(t1);
    int ten = std::get<0>(t2);
    int one = std::get<1>(t2);

    return (thousand * 1000) + (hundred * 100) + (ten * 10) + one;
}

int Move::getMoveID() {
    return id;
}

std::string Move::getRankFile(int row, int col) {
    std::string rankFile = std::string(1, colsToFiles[col]) + std::to_string(rowsToRanks[row]);
    return rankFile;
}
