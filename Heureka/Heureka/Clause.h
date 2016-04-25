//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_CLAUSE_H
#define INC_02180_HEUREKA_CLAUSE_H

#include <vector>
#include <deque>
#include <unordered_set>
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
                                  visited(other.visited), cameFrom(other.cameFrom),
                                  neighbors(other.neighbors){
        updateTotalDistance();
    }

    void updateTotalDistance();
    void addLiteralToClause(Literal& literal);
    void calcHeuristicDistance();
    std::string toString() const;

    // Comparison operators
    bool operator() (const Clause& lhs, const Clause& rhs) const;
    bool operator< (const Clause& rhs) const;
    bool operator== (const Clause& rhs) const;
    bool operator!= (const Clause& rhs) const;
    void operator= (const Clause& rhs);

    Clause resolution(Clause& clause);
    void eliminateDuplicateLiterals(std::unordered_set<Literal> allSymbols,
                                    std::deque<Literal, std::allocator<Literal>> &resolutedSymbols);
    void joinLiterals(std::unordered_set<Literal>& allSymbols,
                      std::deque<Literal, std::allocator<Literal>> &temp);
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
