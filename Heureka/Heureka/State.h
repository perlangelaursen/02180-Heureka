//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_STATE_H
#define INC_02180_HEUREKA_STATE_H

#include <string>
#include <vector>
#include "Point.h"

using neighbor = std::pair<int, std::string>;

namespace Heureka {
    struct State {
        Point point;
        double distanceFromStart;
        double heuristic_distance;
        double totalDistance;
        bool visited = false;
        int cameFrom = -1;
        std::vector<neighbor> neighbors;

        State(double distanceFromStart, double heuristic_distance, const Point point) : point(point), distanceFromStart(
                distanceFromStart), heuristic_distance(heuristic_distance) {
            updateTotalDistance();
        }

        State(const State& other) : point(other.point), distanceFromStart(other.distanceFromStart),
                                    heuristic_distance(other.heuristic_distance),
                                    visited(other.visited),
                                    cameFrom(other.cameFrom), neighbors(other.neighbors){
            updateTotalDistance();
        }


        void updateTotalDistance() {
            totalDistance = distanceFromStart + heuristic_distance;
        }

        bool operator()(const State& lhs, const State& rhs) const {
            return lhs.totalDistance < rhs.totalDistance;
        }

        bool operator< (const State& rhs) const {
            return totalDistance < rhs.totalDistance;
        }

        bool operator== (const State& rhs) const {
            return point == rhs.point;
        }
    };
}

#endif //INC_02180_HEUREKA_STATE_H
