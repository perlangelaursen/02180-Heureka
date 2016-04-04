//
// Created by Per Lange Laursen on 17/03/16.
//


#include "Driver.h"

void Driver::run() {
    readStateSpace();
    readDirections();
}

void Driver::readDirections() {
    std::vector<std::string> temp(2);
    std::ifstream ifs(directions);
    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + directions;
    }
    int startIndex = getIndex(temp, ifs);
    int goalIndex = getIndex(temp, ifs);

    pathfinding.aStar(startIndex, goalIndex);
    ifs.close();
}

int Driver::getIndex(std::vector<std::string> &temp, std::ifstream &ifs) {
    getline(ifs, tempString);
    split(temp, tempString, boost::algorithm::is_any_of(" "));
    return pathfinding.getIndex(boost::lexical_cast<int>(temp[0]), boost::lexical_cast<int>(temp[1]));
}

void Driver::readStateSpace() {
    std::ifstream ifs(file);
    std::vector<std::string> temp(5);

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + file;
    }

    while (getline(ifs, tempString)) {
        split(temp, tempString, boost::algorithm::is_any_of(" "));
        tempX1 = boost::lexical_cast<int>(temp[0]);
        tempY1 = boost::lexical_cast<int>(temp[1]);
        tempX2 = boost::lexical_cast<int>(temp[3]);
        tempY2 = boost::lexical_cast<int>(temp[4]);

        pathfinding.addState(tempX1, tempY1, temp[2], tempX2, tempY2);
    }
    ifs.close();
}

