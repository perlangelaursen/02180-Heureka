//
// Created by Per Lange Laursen on 09/03/16.
//

#ifndef INC_02180_HEUREKA_COMPARATOR_H
#define INC_02180_HEUREKA_COMPARATOR_H

#include "State.h"

namespace Heureka {
    class Comparator;
}

class Comparator {
public:
    int operator() (const Heureka::State s1, const Heureka::State s2) {
        return s1.distanceFromStart > s2.distanceFromStart;
    }
};


#endif //INC_02180_HEUREKA_COMPARATOR_H
