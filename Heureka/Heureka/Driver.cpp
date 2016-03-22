//
// Created by Per Lange Laursen on 17/03/16.
//


#include "Driver.h"

void Driver::run() {
    std::ifstream ifs(file);
    std::vector<std::string> temp(5);

    if(!(ifs.is_open())) {
        std::cerr <<  "Error! Could not open file";
    }

    while (std::getline(ifs, tempString)) {
        boost::split(temp, tempString, boost::is_any_of(" "));
        tempX1 = boost::lexical_cast<int>(temp[0]);
        tempY1 = boost::lexical_cast<int>(temp[1]);
        tempX2 = boost::lexical_cast<int>(temp[3]);
        tempY2 = boost::lexical_cast<int>(temp[4]);

        pathfinding.addState(tempX1, tempY1, temp[2], tempX2, tempY2);
    }
    ifs.close();

    std::ifstream ifs2(directions);
    if(!(ifs2.is_open())) {
        std::cerr <<  "Error! Could not open file";
    }
    std::getline(ifs2, tempString);
    boost::split(temp, tempString, boost::is_any_of(" "));
    int start = boost::lexical_cast<int>(temp[0]);
    int goal = boost::lexical_cast<int>(temp[1]);

    pathfinding.aStar(start, goal);
    ifs2.close();
}

