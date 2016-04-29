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
private:
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y) { }
    double calcEuclideanDistance(Point p);
    double calcEuclideanDistance(int pointx, int pointy);
    int getX() const;
    int getY() const;
    bool operator==(const Point& point) const;
};

#endif //INC_02180_HEUREKA_POINT_H
