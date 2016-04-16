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







