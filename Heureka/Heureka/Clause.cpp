//
// Created by Per Lange Laursen on 12/04/16.
//

#include "Clause.h"

void Clause::updateTotalDistance() {
    totalDistance = distanceFromStart + heuristic_distance;
}

void Clause::addToChildKnowledgeBase(const std::vector<Clause> &local) {

}



