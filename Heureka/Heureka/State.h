//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_STATE_H
#define INC_02180_HEUREKA_STATE_H

#include <string>
#include "Point.h"


namespace Heureka {
    struct State {
        int index;
        int nextPoint;
        double distance;
        double heuristic_distance;
        std::string roadName;

        bool operator()(const State& lhs, const State& rhs) const {
            return lhs.heuristic_distance < rhs.heuristic_distance;
        }
    };
}

#endif //INC_02180_HEUREKA_STATE_H
