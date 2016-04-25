//
// Created by Per Lange Laursen on 12/04/16.
//

#include <iostream>
#include "Clause.h"

Clause::Clause() {

}

Clause::~Clause() {
	//delete cameFrom;
}

void Clause::updateTotalDistance() {
    totalDistance = distanceFromStart + heuristic_distance;
}

void Clause::addLiteralToClause(Literal &literal) {
    symbols.push_back(literal);
}

void Clause::calcHeuristicDistance() {
    heuristic_distance = boost::lexical_cast<double>(symbols.size());
}

std::string Clause::toString() const {
    std::string out("");
    for(const Literal& literal : symbols) {
        out += literal.toString();
        out += " || ";
    }
    out = (out.compare("") == 0) ? "Ø" : out.substr(0, out.length() - 4);
    if (symbols.size() > 1) out = "(" + out +")";
    return out;
}

bool Clause::operator()(const Clause &lhs, const Clause &rhs) const {
    return lhs.totalDistance < rhs.totalDistance;
}

bool Clause::operator<(const Clause &rhs) const {
    return totalDistance < rhs.totalDistance;
}

bool Clause::operator==(const Clause &rhs) const {
    bool isEqual = (rhs.symbols.size() == symbols.size());
    for(Literal symbol : rhs.symbols) {
        if(std::find(symbols.begin(), symbols.end(), symbol) == symbols.end())
            isEqual = false;
    }
    return isEqual;
}

bool Clause::operator!=(const Clause &rhs) const {
    bool isNotEqual = (rhs.symbols.size() != symbols.size());
    for(Literal symbol : rhs.symbols) {
        if(!(std::find(symbols.begin(), symbols.end(), symbol) == symbols.end()))
            isNotEqual = false;
    }
    return isNotEqual;
}

void Clause::operator=(const Clause &rhs) {
    symbols = rhs.symbols;
    neighbors = rhs.neighbors;
    distanceFromStart = rhs.distanceFromStart;
    heuristic_distance = rhs.heuristic_distance;
    totalDistance = rhs.totalDistance;
    visited = rhs.visited;
    cameFrom = rhs.cameFrom;
}

std::ostream &operator<<(std::ostream &os, const Clause &clause) {
    os << clause.toString();
    return os;
}

void Clause::addNeighbor(int neighbor, std::string clause) {
    neighbors.push_back(std::make_pair(neighbor, clause));
}

Clause Clause::resolution(Clause &clause) {
    std::deque<Literal> allSymbols;
    std::deque<Literal> resolutedSymbols;
    if (*this == clause) {
        return *this;
    } else {
        joinLiterals(allSymbols, this->symbols);
        joinLiterals(allSymbols, clause.symbols);

        eliminateDuplicateLiterals(allSymbols, resolutedSymbols);
        Clause result(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        result.setSymbols(resolutedSymbols);
    }

    return Clause();
}

void Clause::eliminateDuplicateLiterals(std::deque<Literal, std::allocator<Literal>> &allSymbols,
                                        std::deque<Literal, std::allocator<Literal>> &resolutedSymbols) {
    for(Literal& l : allSymbols) {
        Literal inverse(l.toString());
        inverse.negated = !inverse.negated;
        if(std::find(allSymbols.begin(), allSymbols.end(), inverse) == allSymbols.end())
            resolutedSymbols.push_back(l);
    }
    if(resolutedSymbols.size() == 0) {
        Literal emptyLiteral("Ø");
        resolutedSymbols.push_back(emptyLiteral);
    }

}

void Clause::joinLiterals(std::deque<Literal, std::allocator<Literal>> &allSymbols,
                          std::deque<Literal, std::allocator<Literal>> &temp) {
    std::deque<Literal>::const_iterator iterator;
    for(iterator = temp.begin(); iterator != temp.end(); ++iterator) {
        allSymbols.push_back(*iterator);
    }
}

