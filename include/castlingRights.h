#ifndef CASTLINGRIGHTS_H
#define CASTLINGRIGHTS_H

#include <iostream>
#include <string>

class CastlingRights {

    public:  

        bool whiteKingSide;
        bool whiteQueenSide;
        bool blackKingSide;
        bool blackQueenSide;

        CastlingRights();
        CastlingRights(bool wks, bool wqs, bool bks, bool bqs);
        CastlingRights(std::string rights);
        ~CastlingRights();
        CastlingRights(const CastlingRights& other);
        CastlingRights& operator=(CastlingRights other);

        std::string toString();
};

#endif