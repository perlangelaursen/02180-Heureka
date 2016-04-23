//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_KNOWLEDGEBASE_H
#define INC_02180_HEUREKA_KNOWLEDGEBASE_H

#include <vector>
#include <iostream>
#include "Clause.h"
#include "Literal.h"

namespace Heureka {
    class KnowledgeBase;
}

class KnowledgeBase {
private :
	void updateClause(Clause &clause, double tempDistanceFromStart, Clause &current);
	void reconstructPath(Clause start, Clause goal);
	void clausalResolution(Clause& clause);
	void eliminateDuplicateLiterals(std::deque<Literal, std::allocator<Literal>> &allSymbols,
									std::deque<Literal, std::allocator<Literal>> &resolutedSymbols);
	void joinLiterals(std::deque<Literal> &to, std::deque<Literal> &symbols);

	std::vector<Clause> clauses;
public:
	void aStar(Clause start, Clause goal);
	void addClause(Clause &clause);
	const std::vector<Clause> &getClauses() const {
		return clauses;
	}

};

#endif //INC_02180_HEUREKA_KNOWLEDGEBASE_H
