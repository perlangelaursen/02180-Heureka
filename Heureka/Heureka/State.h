//
// Created by Per Lange Laursen on 08/03/16.
//

#ifndef INC_02180_HEUREKA_STATE_H
#define INC_02180_HEUREKA_STATE_H

#include <string>
#include "Point.h"


namespace Heureka {
    struct State {
        int nextPoint;
        double distance;
        std::string roadName;

        bool operator> (const State s) const {
            return distance > s.distance;
        }
    };
}

#endif //INC_02180_HEUREKA_STATE_H
