//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_CLAUSE_H
#define INC_02180_HEUREKA_CLAUSE_H

#include <unordered_set>
#include <vector>
#include "Literal.h"

namespace Heureka {
    class Clause;
}

class Clause {
private:
    std::unordered_set<Literal> symbols;
    std::vector<Clause> resolutedClauses;
    std::vector<Clause> localKnowledgeBase;
    std::vector<Clause> childKnowledgeBase;
public:
    double distanceFromStart;
    double heuristic_distance;
    double totalDistance;
    bool visited = false;
};


#endif //INC_02180_HEUREKA_CLAUSE_H
