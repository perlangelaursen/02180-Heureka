//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_PATHFINDING_H
#define INC_02180_HEUREKA_PATHFINDING_H

#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <functional>
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
	std::vector<Heureka::State> states;

	int getIndex(Heureka::State s);
	void aStar(Heureka::State start, Heureka::State goal);
	void reconstructPath(Heureka::State goal);
	int checkIfStateExists(Heureka::State state);
};


#endif //INC_02180_HEUREKA_PATHFINDING_H
