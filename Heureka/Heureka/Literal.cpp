//
// Created by Martin Hansen on 18/04/16.
//

#include "Literal.h"


bool Literal::operator()(const Literal &lhs, const Literal &rhs) const {
    return lhs.negated == rhs.negated && lhs.symbol.compare(rhs.symbol) == 0;
}

bool Literal::operator==(const Literal &rhs) const {
    return negated == rhs.negated && symbol.compare(rhs.symbol) == 0;
}

std::string Literal::toString() const {
    return negated ? "!" + symbol : symbol;
}





