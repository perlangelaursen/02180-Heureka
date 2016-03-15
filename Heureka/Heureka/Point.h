//
// Created by Per Lange Laursen on 03/03/16.
//

#ifndef INC_02180_HEUREKA_POINT_H
#define INC_02180_HEUREKA_POINT_H

#include <cmath>

namespace Heureka {
    class Point;
}
class Heureka::Point {
public:
    Point(int i, int i1) : x(i), y(i1) { }
    double calcEuclideanDistance(Point p);
    double calcEuclideanDistance(int pointx, int pointy);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
};

#endif //INC_02180_HEUREKA_POINT_H
