//
// Created by Per Lange Laursen on 17/03/16.
//

#ifndef INC_02180_HEUREKA_DRIVER_H
#define INC_02180_HEUREKA_DRIVER_H


#include <fstream>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Pathfinding.h"

namespace Heureka {
    class Driver;
}

class Driver {
public:
    void run();
private:
    std::string tempString;
    //std::string file = "Copenhagen.txt";
    std::string file = "Heureka_copenhagen.txt";
    std::string directions = "CopenhagenDirections.txt";
    int tempX1, tempX2, tempY1, tempY2;
    Pathfinding pathfinding;

    void readStateSpace();
    void readDirections();
    int getIndex(std::vector<std::string> &temp, std::ifstream &ifs);
};


#endif //INC_02180_HEUREKA_DRIVER_H
