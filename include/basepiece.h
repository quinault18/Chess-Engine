#ifndef BASEPIECE_H
#define BASEPIECE_H


#include <string>

class BasePiece {
private:
    std::string id;

public: 
    BasePiece(std::string id);
    std::string getID();

    
};

#endif