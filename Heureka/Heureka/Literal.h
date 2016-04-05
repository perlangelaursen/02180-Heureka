//
// Created by Per Lange Laursen on 05/04/16.
//

#ifndef INC_02180_HEUREKA_LITERAL_H
#define INC_02180_HEUREKA_LITERAL_H

#include <string>

struct Literal {
    bool negated = false;
    std::string symbol;

    Literal(const std::string &symbol) {
        this -> negated = symbol.substr(0, 1) == '!';
        this -> symbol = negated ? symbol.substr(1,symbol.size()-1) : symbol;
    }
};

#endif //INC_02180_HEUREKA_LITERAL_H
