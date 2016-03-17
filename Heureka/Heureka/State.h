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
        double distanceFromStart;
        double heuristic_distance;
        double total_distance;
        bool visited;
        Point point;
        std::vector<neighbor> neighbors;

        bool operator()(const State& lhs, const State& rhs) const {
            return lhs.heuristic_distance < rhs.heuristic_distance;
        }

        bool operator== (const State& lhs, const State& rhs) const {
            return lhs.point == rhs.point &&
                    lhs.distanceFromStart == rhs.distanceFromStart &&
                    lhs.heuristic_distance == rhs.heuristic_distance &&
                    lhs.total_distance == rhs.total_distance;
        }
    };
}

#endif //INC_02180_HEUREKA_STATE_H
