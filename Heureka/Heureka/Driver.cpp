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

        std::cout << tempX1 << " " << tempY1 << " " << " " << temp[2] << " " << tempX2 << " " << tempY2 << std::endl;
        pathfinding.addState(tempX1, tempY1, temp[2], tempX2, tempY2);
    }
    ifs.close();
    pathfinding.aStar(12, 3);
}

