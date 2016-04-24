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
    resolutedClauses = rhs.resolutedClauses;
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

std::vector<int> &Clause::getResolutedClauses() {
    return resolutedClauses;
}

void Clause::addNeighbor(int neighbor) {
    resolutedClauses.push_back(neighbor);
}

