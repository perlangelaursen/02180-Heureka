//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_CLAUSE_H
#define INC_02180_HEUREKA_CLAUSE_H

#include <vector>
#include <deque>
#include <boost/lexical_cast.hpp>
#include "Literal.h"

using neighbor = std::pair<int, std::string>;

namespace Heureka {
    class Clause;
}

class Clause {
private:
    std::deque<Literal> symbols;

public:
	Clause();
	~Clause();

    double distanceFromStart;
    double heuristic_distance;
    double totalDistance;
    bool visited = false;
	int cameFrom;
    std::vector<neighbor> neighbors;

    Clause(double distanceFromStart, double heuristic_distance) : distanceFromStart(distanceFromStart),
                                                                  heuristic_distance(heuristic_distance) {
        updateTotalDistance();
    }

    Clause(const Clause& other) : symbols(other.symbols),
                                  distanceFromStart(other.distanceFromStart),
                                  heuristic_distance(other.heuristic_distance),
                                  visited(other.visited) {
        updateTotalDistance();
    }

    void updateTotalDistance();
    void addLiteralToClause(Literal& literal);
    void calcHeuristicDistance();
    std::string toString() const;

    std::vector<neighbor> &getResolutedClauses();

    // Comparison operators
    bool operator() (const Clause& lhs, const Clause& rhs) const;
    bool operator< (const Clause& rhs) const;
    bool operator== (const Clause& rhs) const;
    bool operator!= (const Clause& rhs) const;
    void operator= (const Clause& rhs);

    void addNeighbor(int neighbor, std::string clause);

    friend std::ostream& operator<< (std::ostream& os, const Clause& clause);
    std::deque<Literal, std::allocator<Literal>> &getSymbols() {
        return symbols;
    }

    void setSymbols(const std::deque<Literal, std::allocator<Literal>> &symbols) {
        Clause::symbols = symbols;
    }
};


#endif //INC_02180_HEUREKA_CLAUSE_H
