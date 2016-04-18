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

		for (auto neighbor : current.getResolutedClauses()) {
			if (neighbor.visited) {
				continue;
			}

			tempDistanceFromStart = current.distanceFromStart + 1;
			iterator = std::find(queue.begin(), queue.end(), neighbor);

			if (iterator == queue.end()) {
				updateClause(neighbor, tempDistanceFromStart, current);

				queue.push_front(neighbor);
			}
			else if (tempDistanceFromStart >= neighbor.distanceFromStart) {
				continue;
			}
			else {
				updateClause(neighbor, tempDistanceFromStart, current);

				iterator->cameFrom = neighbor.cameFrom;
				iterator->distanceFromStart = neighbor.distanceFromStart;
				iterator->heuristic_distance = neighbor.heuristic_distance;
				iterator->updateTotalDistance();
			}
		}
	}

}

void KnowledgeBase::updateClause(Clause &clause, double tempDistanceFromStart, Clause current) {
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
	}

	for (auto s : path) {
		std::cout << s << "\n";
	}
}
