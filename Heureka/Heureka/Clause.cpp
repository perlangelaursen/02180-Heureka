//
// Created by Per Lange Laursen on 12/04/16.
//

#include "Clause.h"

Clause::Clause() {

}

Clause::~Clause() {

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
    std::string out = convertLiteralsToString();
    out = checkIfLiteralStringIsEmpty(out);
    if (symbols.size() > 1) out = "(" + out +")";
    return out;
}

std::basic_string<char, std::char_traits<char>> Clause::checkIfLiteralStringIsEmpty(const std::string &out) const {
    return (out.compare("") == 0) ? "Ø" : out.substr(0, out.length() - 4);
}

std::string Clause::convertLiteralsToString() const {
    std::string out("");
    for(auto iter = symbols.cbegin(); iter != symbols.cend(); ++iter) {
        out += iter -> toString();
        out += " || ";
    }
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
    for(auto iterator = rhs.symbols.cbegin(); iterator != rhs.symbols.cend(); ++iterator) {
        if(std::find(symbols.begin(), symbols.end(), *iterator) == symbols.end())
            isEqual = false;
    }
    return isEqual;
}

bool Clause::operator!=(const Clause &rhs) const {
    return !(*this == rhs);
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
    std::unordered_set<Literal> allSymbols;
    std::deque<Literal> resolutedSymbols;
    if (*this == clause) {
        return *this;
    } else {
        joinLiterals(allSymbols, this->symbols);
        joinLiterals(allSymbols, clause.symbols);

        eliminateDuplicateLiterals(allSymbols, resolutedSymbols);
        Clause result(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        result.setSymbols(resolutedSymbols);
        return result;
    }
}

void Clause::eliminateDuplicateLiterals(std::unordered_set<Literal> allSymbols,
                                        std::deque<Literal, std::allocator<Literal>> &resolutedSymbols) {
    for(auto iter = allSymbols.cbegin(); iter != allSymbols.cend(); ++iter) {
        Literal inverse(iter -> toString());
        inverse.negated = !inverse.negated;
        if(std::find(allSymbols.begin(), allSymbols.end(), inverse) == allSymbols.end())
            resolutedSymbols.push_back(*iter);
    }
}

void Clause::joinLiterals(std::unordered_set<Literal>& allSymbols,
                          std::deque<Literal, std::allocator<Literal>> &temp) {
    for(auto iterator = temp.cbegin(); iterator != temp.cend(); ++iterator) {
        allSymbols.insert(*iterator);
    }
}

void Clause::setSymbols(const std::deque<Literal, std::allocator<Literal>> &symbols) {
    Clause::symbols = symbols;
}



