//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_PATHFINDING_H
#define INC_02180_HEUREKA_PATHFINDING_H


#include <vector>
#include "Point.h"
#include "State.h"

namespace Heureka {
    class Pathfinding;
}

class Pathfinding {
public:
    void addState(int x1, int y1, std::string roadName, int x2, int y2);

private:
    std::vector<Heureka::Point> points;
    std::vector<std::vector<Heureka::State>> states;

    int pointExists(Heureka::Point);
    int addPoint(int x, int y);
};


#endif //INC_02180_HEUREKA_PATHFINDING_H
