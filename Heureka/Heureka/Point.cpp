//
// Created by Per Lange Laursen on 03/03/16.
//

#include "Point.h"

double Heureka::Point::calcEuclideanDistance(Heureka::Point p) {
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double Heureka::Point::calcEuclideanDistance(int x, int y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}
