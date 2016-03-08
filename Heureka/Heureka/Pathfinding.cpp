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
    return 0;
}

void Pathfinding::addState(int x1, int y1, std::string roadName, int x2, int y2) {
    Heureka::Point p1(x1, y1);
    Heureka::Point p2(x2, y2);
    Heureka::State temp;
    temp.roadName = roadName;
    temp.distance = p1.calcEuclideanDistance(p2);
    temp.nextPoint = addPoint(x2, y2);
    int state1 = addPoint(x1, y1);
    states.resize(states.size() + 1);
    states[state1].push_back(temp);
}
