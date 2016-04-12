//
// Created by Per Lange Laursen on 12/04/16.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "InferenceReader.h"


void InferenceReader::run() {
    readKB();
    readEntailed();
}

void InferenceReader::readKB() {
    std::vector temp(100);
    std::string tempString;
    std::ifstream ifs(KB);

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + KB;
    }

    while (getline(ifs, tempString)) {

    }
    ifs.close();

}

void InferenceReader::readEntailed() {
    std::vector temp(100);
    std::string tempString;
    std::ifstream ifs(KB);

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + KB;
    }

    getline(ifs, tempString);
    ifs.close();
}





