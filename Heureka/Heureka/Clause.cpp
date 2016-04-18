//
// Created by Per Lange Laursen on 12/04/16.
//

#include "Clause.h"

void Clause::updateTotalDistance() {
    totalDistance = distanceFromStart + heuristic_distance;
}

void Clause::addToChildKnowledgeBase(const std::vector<Clause> &local) {
    std::vector<Clause>::const_iterator iterator;
    for(iterator = local.begin(); iterator != local.end(); ++iterator) {
        childKnowledgeBase.push_back(*iterator);
    }
    childKnowledgeBase.push_back(*this);
}

void Clause::addLiteralToClause(Literal &literal) {
    symbols.push_front(literal);
}

void Clause::calcHeuristicDistance() {
    heuristic_distance = boost::lexical_cast<double>(symbols.size());
}

std::string Clause::toString() {
    std::string out("");
    for(auto literal : symbols) {
        out += literal.toString();
        out += " || ";
    }
    out = (out.compare("") == 0) ? "Ø" : out.substr(0, out.length() - 4);
    if (symbols.size() > 1) out = "(" + out +")";
    return out;
}

bool Clause::operator()(const Clause &lhs, const Clause &rhs) {
    return lhs.totalDistance < rhs.totalDistance;
}

bool Clause::operator<(const Clause &rhs) {
    return totalDistance < rhs.totalDistance;
}

bool Clause::operator==(const Clause &rhs) {
    return symbols.size() == rhs.symbols.size() && symbols == rhs.symbols;
}















