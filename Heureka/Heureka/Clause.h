//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_CLAUSE_H
#define INC_02180_HEUREKA_CLAUSE_H

#include <vector>
#include <deque>
#include <boost/lexical_cast.hpp>
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

    Clause(const std::vector<Clause> &localKnowledgeBase, double distanceFromStart, double heuristic_distance)
            : localKnowledgeBase(localKnowledgeBase), distanceFromStart(distanceFromStart),
              heuristic_distance(heuristic_distance) {
        updateTotalDistance();
        addToChildKnowledgeBase(localKnowledgeBase);
    }


    Clause(const std::vector<Clause> &localKnowledgeBase) : localKnowledgeBase(localKnowledgeBase) {
        addToChildKnowledgeBase(localKnowledgeBase);
    }

    Clause(const Clause& other) : symbols(other.symbols), localKnowledgeBase(other.localKnowledgeBase),
                                  childKnowledgeBase(other.childKnowledgeBase),
                                  distanceFromStart(other.distanceFromStart),
                                  heuristic_distance(other.heuristic_distance), visited(other.visited) {
        updateTotalDistance();
    }

    void addToChildKnowledgeBase(const std::vector<Clause> &local);
    void updateTotalDistance();
    void addLiteralToClause(Literal& literal);
    void calcHeuristicDistance();
    std::string toString();



    // Comparison operators
    bool operator() (const Clause& lhs, const Clause& rhs);
    bool operator< (const Clause& rhs);
    bool operator== (const Clause& rhs);
};


#endif //INC_02180_HEUREKA_CLAUSE_H
