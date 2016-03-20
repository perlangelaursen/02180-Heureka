//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_STATE_H
#define INC_02180_HEUREKA_STATE_H

#include <string>
#include "Point.h"

typedef std::pair<int, std::string> neighbor;

namespace Heureka {
    struct State {
        Point point;
        double distanceFromStart;
        double heuristic_distance;
        bool visited = false;
        int cameFrom = -1;
        std::vector<neighbor> neighbors;


        State(double distanceFromStart, double heuristic_distance, const Point point) : distanceFromStart(
                distanceFromStart), heuristic_distance(heuristic_distance), point(point) { }

        bool operator()(const State& lhs, const State& rhs) const {
            return lhs.heuristic_distance < rhs.heuristic_distance;
        }

        bool operator< (const State& rhs) const {
            return heuristic_distance < rhs.heuristic_distance;
        }

        bool operator== (const State& rhs) const {
            return point == rhs.point;
        }
    };
}

#endif //INC_02180_HEUREKA_STATE_H
