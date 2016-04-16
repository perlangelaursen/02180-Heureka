//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_CLAUSE_H
#define INC_02180_HEUREKA_CLAUSE_H

#include <unordered_set>
#include <vector>
#include <deque>
#include "Literal.h"

namespace Heureka {
    class Clause;
}

class Clause {
private:
    std::deque<Literal> symbols;
    std::vector<Clause> resolutedClauses;
    std::vector<Clause> localKnowledgeBase;
    std::vector<Clause> childKnowledgeBase;
public:
    double distanceFromStart;
    double heuristic_distance;
    double totalDistance;
    bool visited = false;


    Clause(const std::vector<Clause> &localKnowledgeBase) : localKnowledgeBase(localKnowledgeBase) { }

    Clause(const std::vector<Clause> &localKnowledgeBase, double distanceFromStart, double heuristic_distance)
            : localKnowledgeBase(localKnowledgeBase), distanceFromStart(distanceFromStart),
              heuristic_distance(heuristic_distance) {
        updateTotalDistance();
    }

    void addToChildKnowledgeBase(const std::vector<Clause> &local);
    void updateTotalDistance();
};


#endif //INC_02180_HEUREKA_CLAUSE_H
