//
// Created by Per Lange Laursen on 12/04/16.
//

#ifndef INC_02180_HEUREKA_INFERENCEREADER_H
#define INC_02180_HEUREKA_INFERENCEREADER_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/tokenizer.hpp>
#include "KnowledgeBase.h"

namespace Heureka {
    class InferenceDriver;
}

class InferenceDriver {
public:
    void run();

private:
    std::string KB = "KnowledgeBase.txt";
    std::string entailed = "Entailed.txt";
    KnowledgeBase knowledgeBase;

    void readKB();
    Literal readEntailed();
    void runAStar();
};


#endif //INC_02180_HEUREKA_INFERENCEREADER_H
