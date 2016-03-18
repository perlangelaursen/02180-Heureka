//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_PATHFINDING_H
#define INC_02180_HEUREKA_PATHFINDING_H

#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <list>
#include "Point.h"
#include "State.h"
#include "Comparator.h"

namespace Heureka {
    class Pathfinding;
}

class Pathfinding {
public:
    void addState(int x1, int y1, std::string roadName, int x2, int y2);
	void aStar(int startIndex, int goalIndex);

	Pathfinding() { }

private:
	std::list<Heureka::State> openSet;
	//std::priority_queue<Heureka::State, Comparator> priorityQueue; // List of all states
    std::vector<Heureka::Point> points;
	std::vector<Heureka::State> states;
    std::vector<std::vector<Heureka::State>> graph; // List of neighbors
	std::vector<double> distancesToStart; // Length of path from start to current node
	std::vector<double> distancesToGoal; // Distance from current node to goal
	std::vector<int> cameFrom;
	std::vector<int> visited;

	int getIndex(Heureka::Point p);

    int pointExists(Heureka::Point);
	void aStar(Heureka::State start, Heureka::State goal);
    int addPoint(int x, int y);
	bool isVisited(int neighbor);
	void reconstructPath(int startIndex, int goalIndex);
	int checkIfStateExists(Heureka::State state);
};


#endif //INC_02180_HEUREKA_PATHFINDING_H
