#include "basepiece.h"

BasePiece::BasePiece(std::string id) : id(id) {}

std::string BasePiece::getID() {
    return id;
}