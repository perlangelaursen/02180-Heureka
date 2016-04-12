//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_NODE_H
#define INC_02180_HEUREKA_NODE_H

#include "INode.h"

namespace Heureka {
    class Node;
}

class Node : public INode {
public:
    double distanceFromStart;
    double heuristic_distance;
    double totalDistance;
    bool visited = false;
    int cameFrom = -1;



    Node(double heuristic_distance, double distanceFromStart) : heuristic_distance(heuristic_distance),
                                                                distanceFromStart(distanceFromStart) {
        updateTotalDistance();
    }

    Node(const Node& other) : heuristic_distance(other.heuristic_distance),
                              distanceFromStart{other.distanceFromStart} {
        updateTotalDistance();
    }

    void updateTotalDistance() {
        totalDistance = distanceFromStart + heuristic_distance;
    }

    virtual double estimateHeuristicDistance(INode otherNode) override {
        return 0;
    }

    virtual bool operator()(const INode &lhs, const INode &rhs) override {
        return false;
    }

    virtual bool operator<(const INode &rhs) override {
        return false;
    }

    virtual bool operator==(const INode &rhs) override {
        return false;
    }


};


#endif //INC_02180_HEUREKA_NODE_H
