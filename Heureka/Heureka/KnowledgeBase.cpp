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
		clausalResolution(currentIndex);

		for (auto neighbor : clauses[currentIndex].neighbors) {
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
				updateItemInQueue(iterator, index);
			}
		}
	}
}

void KnowledgeBase::updateItemInQueue(std::deque<Clause>::iterator &iterator, int index) const {
	iterator->cameFrom = clauses[index].cameFrom;
	iterator->distanceFromStart = clauses[index].distanceFromStart;
	iterator->heuristic_distance = clauses[index].heuristic_distance;
	iterator->updateTotalDistance();
}

void KnowledgeBase::reconstructPath(int start, int goal) {
	std::deque<std::string> path;
	int currentIndex = goal;
	int previousIndex;
	std::vector<std::pair<int, std::string>>::iterator iterator;
	while (currentIndex != start) {
		previousIndex = clauses[currentIndex].cameFrom;
		iterator = std::find_if(clauses[previousIndex].neighbors.begin(), clauses[previousIndex].neighbors.end(),
								[currentIndex](const std::pair<int, std::string> element) {
									return element.first == currentIndex;
								});
		path.push_front(clauses[previousIndex].toString() + " && " + iterator -> second + " => " +
						clauses[currentIndex].toString());
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

int KnowledgeBase::getIndex(Clause &clause) {
	auto iterator = std::find(clauses.begin(), clauses.end(), clause);
	if(iterator != clauses.end()) {
		return boost::lexical_cast<int>(std::distance(clauses.begin(), iterator));
	}
	return -1;
}

void KnowledgeBase::clausalResolution(int index) {
	for(int i = 0; i < clauses.size(); i++) {
		Clause result = clauses[index].resolution(clauses[i]);
		std::cout << clauses[index] << " && " << clauses[i] << " => " << result << "\n";
		bool isNotInClauses = true;
		for(int j = 0; j < clauses.size(); j++) {
			if(result == clauses[j]) isNotInClauses = false;
		}
		if(isNotInClauses) {
			clauses.push_back(result);
			clauses[index].addNeighbor(boost::lexical_cast<int>(clauses.size() - 1), clauses[i].toString());
		}
	}
}

const std::vector<Clause> &KnowledgeBase::getClauses() const {
	return clauses;
}



