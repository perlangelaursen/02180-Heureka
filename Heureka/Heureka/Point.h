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
    Point(int x, int y) : x(x), y(y) { }
    double calcEuclideanDistance(Point p);
    double calcEuclideanDistance(int x, int y);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
};

#endif //INC_02180_HEUREKA_POINT_H
