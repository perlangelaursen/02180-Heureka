//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_INODE_H
#define INC_02180_HEUREKA_INODE_H


#include <ostream>

namespace Heureka {
    class INode;
}

class INode {
public:
    virtual ~INode()  = default;
    virtual double estimateHeuristicDistance(INode otherNode) = 0;
    virtual friend std::ostream operator<<(std::ostream& os, const INode& iNode) = 0;
    virtual bool operator() (const INode& lhs, const INode& rhs) = 0;
    virtual bool operator< (const INode& rhs) = 0;
    virtual bool operator== (const INode& rhs) = 0;
};


#endif //INC_02180_HEUREKA_INODE_H
