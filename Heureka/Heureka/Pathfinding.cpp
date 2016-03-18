//
// Created by Per Lange Laursen on 08/03/16.
//

#include "Pathfinding.h"

int Pathfinding::addPoint(int x, int y) {
    Heureka::Point point(x, y);
    int returnValue = pointExists(point);
    if(returnValue == -1) {
        points.push_back(point);
        returnValue = (int) points.size() -1;
    }
    return returnValue;
}

int Pathfinding::pointExists(Heureka::Point point) {
    int i = 0;
    for(std::vector<Heureka::Point>::const_iterator iterator = points.begin();
            iterator != points.end(); ++iterator) {
        if((iterator -> getX()) == point.getX() && (iterator -> getY()) == point.getY()) {
            return i;
        }
        ++i;
    }
    return -1;
}

void Pathfinding::addState(int x1, int y1, std::string roadName, int x2, int y2) {
    Heureka::Point point1(x1, y1);
    Heureka::State temp1;
    temp1.point = point1;
    temp1.distanceFromStart = std::numeric_limits<double>::max();
    temp1.heuristic_distance = std::numeric_limits<double>::max();
    temp1.total_distance = std::numeric_limits<double>::max();


    Heureka::Point point2(x2, y2);
    Heureka::State temp2;
    temp2.point = point2;
    temp2.distanceFromStart = std::numeric_limits<double>::max();
    temp2.heuristic_distance = std::numeric_limits<double>::max();
    temp2.total_distance = std::numeric_limits<double>::max();

    int index1 = checkIfStateExists(temp1);
    int index2 = checkIfStateExists(temp2);
    states[index1].neighbors.push_back(std::make_pair(index2, roadName));
}

void Pathfinding::aStar(Heureka::State start, Heureka::State goal) {
	/*
	int startIndex = start.index;
	int goalIndex = goal.index;

	for (auto& i : distancesToStart) {
		i = std::numeric_limits<double>::max();
	}
	for (auto& i : distancesToGoal) {
		i = std::numeric_limits<double>::max();
	}
	for (auto& i : cameFrom) {
		i = -1;
	}

	distancesToStart[startIndex] = 0;
	distancesToGoal[startIndex] = points[startIndex].calcEuclideanDistance(points[goalIndex]);
	states[startIndex].heuristic_distance = distancesToGoal[startIndex];
	openSet.push_front(start);

	while (!openSet.empty()) {
		std::sort(openSet.begin(), openSet.end());
		int currentPointIndex = openSet.front().index;
		if (currentPointIndex == goalIndex) {
			reconstructPath(startIndex, goalIndex);
			break;
		}
		openSet.pop_front();
		visited.push_back(currentPointIndex);

		for (auto i : graph[currentPointIndex]) {
			if (i.visited) {
				continue; // Have been there before
			}
			double temporaryDistance = distancesToStart[currentPointIndex] + i.distanceFromStart;
			if(std::find(openSet.begin(), openSet.end(), i) != openSet.end()) {
				i.heuristic_distance = temporaryDistance + points[i].calcEuclideanDistance(points[goalIndex]);
				openSet.push_back(i);
			} else if (temporaryDistance >= distancesToStart[i.nextPoint]) {
				continue;
			}

			cameFrom[i.nextPoint] = currentPointIndex;
			distancesToStart[i.nextPoint] = temporaryDistance;
			distancesToGoal[i.nextPoint] = temporaryDistance +
					(points[i.nextPoint].calcEuclideanDistance(points[goalIndex]));
		}
	}*/

	/*
	int startIndex = getIndex(start);
	int goalIndex = getIndex(goal);

	for (auto& i : distancesToStart) {
		i = std::numeric_limits<double>::max();
	}
	for (auto& i : distancesToGoal) {
		i = std::numeric_limits<double>::max();
	}
	for (auto& i : cameFrom) {
		i = -1;
	}

	distancesToStart[startIndex] = 0;
	distancesToGoal[startIndex] = start.calcEuclideanDistance(goal);
	openSet.push_front(startIndex);
	//priorityQueue.push(start);

	while (!openSet.empty()) {
		int currentPointIndex = openSet.front();
		if (currentPointIndex == goalIndex) {
			reconstructPath(startIndex, goalIndex);
			break;
		}

		openSet.pop_front();
		visited.push_back(currentPointIndex);
		for (auto i : graph[currentPointIndex]) {
			if (isVisited(i.nextPoint)) {
				continue; // Have been there before
			}
			double temporaryDistance = distancesToStart[currentPointIndex] + i.distanceFromStart;
			if (temporaryDistance <= distancesToStart[i.nextPoint]) {
				priorityQueue.push(points[i.nextPoint]);
			}
			else {
				continue;
			}

			cameFrom[i.nextPoint] = currentPointIndex;
			distancesToStart[i.nextPoint] = temporaryDistance;
			distancesToGoal[i.nextPoint] = temporaryDistance + (points[i.nextPoint].calcEuclideanDistance(goal));
		}
	}*/
}


int Pathfinding::getIndex(Heureka::Point p) {
	int index = 0;
	for (auto& point : points) {
		if (point == p) return index;
		++index;
	}
}

bool Pathfinding::isVisited(int neighbor) {
	for (int i : visited) {
		if (i == neighbor) {
			return true;
		}
	}
	return false;
}

void Pathfinding::reconstructPath(int startIndex, int goalIndex) {
	std::vector<int> totalPath;
	totalPath.push_back(goalIndex);
	int currentIndex = goalIndex;
	while (currentIndex != startIndex) {
		currentIndex = cameFrom[currentIndex];
		totalPath.insert(totalPath.begin(), currentIndex);
	}
	for (int i = 0; i < totalPath.size(); i++) {
		//std::cout << states[i].roadName << std::endl;
	}
}

int Pathfinding::checkIfStateExists(Heureka::State state) {
    bool inSet = false;
    int i = 0;
    for(Heureka::State s : states) {
        if(state == s) {
            inSet = true;
        }
    }
    if(!inSet) {
        states.push_back(state);
        i = (int) (states.size() - 1);
    }
    return i;
}

void Pathfinding::aStar(int startIndex, int goalIndex) {
    Heureka::State start = states[startIndex];
    Heureka::State goal = states[goalIndex];
    aStar(start, goal);
}




