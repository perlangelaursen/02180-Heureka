//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_ARC_H
#define INC_02180_HEUREKA_ARC_H

#include <string>
#include "Node.h"


namespace Heureka {
    struct Arc {
        Node node;
        std::string name;


        Arc(const Node &node, const std::string &name) : node(node), name(name) { }
    };
}

#endif //INC_02180_HEUREKA_ARC_H
