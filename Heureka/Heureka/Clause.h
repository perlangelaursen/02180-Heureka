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
	Clause* cameFrom;

    Clause();

    Clause(const std::vector<Clause> &localKnowledgeBase, double distanceFromStart, double heuristic_distance)
            : localKnowledgeBase(localKnowledgeBase), distanceFromStart(distanceFromStart),
              heuristic_distance(heuristic_distance) {
        updateTotalDistance();
        addToChildKnowledgeBase(localKnowledgeBase);
    }


    Clause(double distanceFromStart, double heuristic_distance) : distanceFromStart(distanceFromStart),
                                                                  heuristic_distance(heuristic_distance) {
        updateTotalDistance();
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


    ~Clause() {
        delete cameFrom;
    }

    void addToChildKnowledgeBase(const std::vector<Clause> &local);
    void updateTotalDistance();
    void addLiteralToClause(Literal& literal);
    void calcHeuristicDistance();
    std::string toString() const;

    std::vector<Clause> &getResolutedClauses();
    Clause clausalResolution(Clause &clause);
    void addLiterals(std::deque<Literal> &to, std::deque<Literal> &symbols);
    void eliminateDuplicates(std::deque<Literal, std::allocator<Literal>> &allSymbols,
                             std::deque<Literal, std::allocator<Literal>> &resolutedSymbols) const;

    // Comparison operators
    bool operator() (const Clause& lhs, const Clause& rhs) const;
    bool operator< (const Clause& rhs) const;
    bool operator== (const Clause& rhs) const;
    bool operator!= (const Clause& rhs) const;
    friend std::ostream& operator<< (std::ostream& os, const Clause& clause);
};


#endif //INC_02180_HEUREKA_CLAUSE_H
