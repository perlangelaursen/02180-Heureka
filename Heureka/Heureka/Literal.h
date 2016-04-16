//
// Created by Per Lange Laursen on 05/04/16.
//

#ifndef INC_02180_HEUREKA_LITERAL_H
#define INC_02180_HEUREKA_LITERAL_H

#include <string>

namespace Heureka {
    struct Literal;
}

struct Literal {
    bool negated = false;
    std::string symbol;

    Literal(const std::string &symbol) {
        this -> negated = symbol.compare(0,1,"!") == 0;
        this -> symbol = negated ? symbol.substr(1,symbol.size()-1) : symbol;
    }

    bool operator() (const Literal& lhs, const Literal& rhs) {
        return lhs.negated == rhs.negated && lhs.symbol.compare(rhs.symbol);
    }

    bool operator== (const Literal& rhs) {
        return negated == rhs.negated && symbol.compare(rhs.symbol);
    }

    std::string toString() const {
        return negated ? "!" + symbol : symbol;
    }

    friend std::ostream& operator<< (std::ostream& os, const Literal& literal) {
        os << literal.toString();
        return os;
    }
};

namespace std {
    template <> struct hash<Literal> {
        size_t operator() (const Literal& literal) const {
            return hash<std::string>()(literal.toString());
        }
    };
}

#endif //INC_02180_HEUREKA_LITERAL_H
