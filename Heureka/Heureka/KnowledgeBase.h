//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_KNOWLEDGEBASE_H
#define INC_02180_HEUREKA_KNOWLEDGEBASE_H

#include <vector>
#include <algorithm>
#include <limits>
#include <functional>
#include <iostream>
#include <deque>
#include <boost/lexical_cast.hpp>
#include "Clause.h"
#include "Literal.h"

namespace Heureka {
    class KnowledgeBase;
}

class KnowledgeBase {
private :
	void reconstructPath(int start, int goal);
	void clausalResolution(int index);
	int getIndex(Clause& clause);
	std::vector<Clause> clauses;

public:
	void aStar(int start, Clause goal);
	void addClause(Clause &clause);
	const std::vector<Clause> &getClauses() const;
	void updateClause(int clause, double tempDistanceFromStart, int current);
	void updateItemInQueue(std::deque<Clause>::iterator &iterator, int index) const;
};

#endif //INC_02180_HEUREKA_KNOWLEDGEBASE_H
