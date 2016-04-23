//
// Created by Martin Hansen on 18/04/16.
//

#include "KnowledgeBase.h"

void KnowledgeBase::aStar(Clause start, Clause goal) {
	std::deque<Clause> queue; // Open set, frontier, to be visited

	start.distanceFromStart = 0;
	start.calcHeuristicDistance();
	start.updateTotalDistance();
	
	queue.push_back(start);

	double tempDistanceFromStart;
	std::deque<Clause>::iterator iterator;

	while (!queue.empty()) {
		std::sort(queue.begin(), queue.end());
		Clause current = queue.front();

		if (current == goal) {
			reconstructPath(start, goal);
			queue.clear();
			break;
		}

		queue.pop_front();
		current.visited = true;

		std::vector<Clause*> neighbors = current.getResolutedClauses();
		for (auto neighbor : neighbors) {
			if (neighbor -> visited) {
				continue;
			}

			tempDistanceFromStart = current.distanceFromStart + current.heuristic_distance;
			iterator = std::find(queue.begin(), queue.end(), *neighbor);

			if (iterator == queue.end()) {
				updateClause(*neighbor, tempDistanceFromStart, current);

				queue.push_front(*neighbor);
			}
			else if (tempDistanceFromStart >= neighbor -> distanceFromStart) {
				continue;
			}
			else {
				updateClause(*neighbor, tempDistanceFromStart, current);

				iterator->cameFrom = neighbor -> cameFrom;
				iterator->distanceFromStart = neighbor -> distanceFromStart;
				iterator->heuristic_distance = neighbor -> heuristic_distance;
				iterator->updateTotalDistance();
			}
		}
	}

}

void KnowledgeBase::updateClause(Clause &clause, double tempDistanceFromStart, Clause &current) {
	clause.cameFrom = &current;
	clause.distanceFromStart = tempDistanceFromStart;
	clause.calcHeuristicDistance();
	clause.updateTotalDistance();
}

void KnowledgeBase::reconstructPath(Clause start, Clause goal) {
	std::deque<std::string> path;
	Clause current = goal;
	Clause *previous;

	while (current != start) {
		previous = current.cameFrom;
		path.push_front(previous->toString());
		current = *previous;
	}

	for (auto s : path) {
		std::cout << s << "\n";
	}
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
		if(std::find(clauses.begin(), clauses.end(), result) == clauses.end()) {
			clauses.push_back(result);
			clause.addNeighbor(&clauses[clauses.size() -1 ]);
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
}








