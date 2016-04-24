//
// Created by Martin Hansen on 18/04/16.
//

#include "KnowledgeBase.h"

void KnowledgeBase::aStar(int start, Clause goal) {
	std::deque<Clause> queue; // Open set, frontier, to be visited

	clauses[start].distanceFromStart = 0;
	clauses[start].calcHeuristicDistance();
	clauses[start].updateTotalDistance();
	
	queue.push_back(clauses[start]);

	double tempDistanceFromStart;
	std::deque<Clause>::iterator iterator;

	while (!queue.empty()) {
		std::sort(queue.begin(), queue.end());
		int currentIndex = getIndex(queue.front());

		if (clauses[currentIndex] == goal) {
			reconstructPath(start, currentIndex);
			queue.clear();
			break;
		}

		queue.pop_front();
		clauses[currentIndex].visited = true;
		clausalResolution(clauses[currentIndex]);

		std::vector<std::pair<int, std::string>> neighbors = clauses[currentIndex].getResolutedClauses();
		for (auto neighbor : neighbors) {
			int index = neighbor.first;
			if (clauses[index].visited) {
				continue;
			}

			tempDistanceFromStart = clauses[currentIndex].distanceFromStart + 1;
			iterator = std::find(queue.begin(), queue.end(), clauses[index]);

			if (iterator == queue.end()) {
				updateClause(index, tempDistanceFromStart, currentIndex);
				queue.push_front(clauses[index]);
			}
			else if (tempDistanceFromStart >= clauses[index].distanceFromStart) {
				continue;
			}
			else {
				updateClause(index, tempDistanceFromStart, currentIndex);
				iterator->cameFrom = clauses[index].cameFrom;
				iterator->distanceFromStart = clauses[index].distanceFromStart;
				iterator->heuristic_distance = clauses[index].heuristic_distance;
				iterator->updateTotalDistance();
			}
		}
	}

}

void KnowledgeBase::reconstructPath(int start, int goal) {
	std::deque<std::string> path;
	int currentIndex = goal;
	int previousIndex;
	path.push_front(clauses[goal].toString());
	while (currentIndex != start) {
		previousIndex = clauses[currentIndex].cameFrom;
		path.push_front(clauses[previousIndex].toString());
		currentIndex = previousIndex;
	}
	std::cout << "Resolution:\n";
	for (auto s : path) {
		std::cout << s << "\n";
	}
}

void KnowledgeBase::updateClause(int clause, double tempDistanceFromStart, int current) {
	clauses[clause].cameFrom = current;
	clauses[clause].distanceFromStart = tempDistanceFromStart;
	clauses[clause].calcHeuristicDistance();
	clauses[clause].updateTotalDistance();
}

void KnowledgeBase::addClause(Clause &clause) {
	clauses.push_back(clause);
}

void KnowledgeBase::clausalResolution(Clause &clause) {
	for(auto c : clauses) {
		std::deque<Literal> allSymbols;
		std::deque<Literal> resolutedSymbols;
		joinLiterals(allSymbols, clause.getSymbols());
		joinLiterals(allSymbols, c.getSymbols());

		eliminateDuplicateLiterals(allSymbols, resolutedSymbols);
		Clause result(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

		result.setSymbols(resolutedSymbols);
		auto iterator = std::find(clauses.begin(), clauses.end(), result);
		if(iterator == clauses.end()) {
			clauses.push_back(result);
			clause.addNeighbor(boost::lexical_cast<int>(clauses.size() - 1), c.toString());
		} else if (clause == result) {
			continue;
		} else {
			clause.addNeighbor(boost::lexical_cast<int>(std::distance(clauses.begin(), iterator)), c.toString());
		}
	}
}

void KnowledgeBase::joinLiterals(std::deque<Literal> &to, std::deque<Literal> &symbols) {
	std::deque<Literal>::const_iterator iterator;
	for(iterator = symbols.begin(); iterator != symbols.end(); ++iterator) {
		to.push_back(*iterator);
	}
}

void KnowledgeBase::eliminateDuplicateLiterals(std::deque<Literal, std::allocator<Literal>> &allSymbols,
											   std::deque<Literal, std::allocator<Literal>> &resolutedSymbols) {
	for(Literal& l : allSymbols) {
		Literal inverse(l.toString());
		inverse.negated = !inverse.negated;
		if(std::find(allSymbols.begin(), allSymbols.end(), inverse) == allSymbols.end())
			resolutedSymbols.push_back(l);
	}
	if(resolutedSymbols.size() == 0) {
		Literal emptyLiteral("Ø");
		resolutedSymbols.push_back(emptyLiteral);
	}
}

int KnowledgeBase::getIndex(Clause &clause) {
	auto iterator = std::find(clauses.begin(), clauses.end(), clause);
	if(iterator != clauses.end()) {
		return boost::lexical_cast<int>(std::distance(clauses.begin(), iterator));
	}
	return -1;
}