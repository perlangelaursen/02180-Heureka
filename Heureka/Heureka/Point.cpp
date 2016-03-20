//
// Created by Per Lange Laursen on 03/03/16.
//

#include "Point.h"

double Heureka::Point::calcEuclideanDistance(Heureka::Point p) {
    return sqrt(pow(x-p.getX(), 2) + pow(y-p.getY(), 2));
}

double Heureka::Point::calcEuclideanDistance(int pointx, int pointy) {
    return sqrt(pow(x - pointx, 2) + pow(y - pointy, 2));
}

int Heureka::Point::getX() const {
    return x;
}

int Heureka::Point::getY() const {
    return y;
}


