//
// Created by Per Lange Laursen on 12/04/16.
//

#include "InferenceDriver.h"


void InferenceDriver::run() {
    readKB();
    readEntailed();
    runAStar();
}

void InferenceDriver::readKB() {
    std::string tempString;
    std::ifstream ifs(KB);
    boost::char_separator<char> separator(",");

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + KB;
    }

    while (getline(ifs, tempString)) {
        boost::tokenizer<boost::char_separator<char>> tokenizer(tempString, separator);
        Clause clause(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        for(const auto t : tokenizer) {
            Literal literal(t);
            clause.addLiteralToClause(literal);
        }
        knowledgeBase.addClause(clause);
    }
    ifs.close();

}

void InferenceDriver::readEntailed() {
    std::string tempString;
    std::ifstream ifs(entailed);

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + entailed;
    }

    getline(ifs, tempString);
    Clause clause(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Literal literal(tempString);
    clause.addLiteralToClause(literal);
    knowledgeBase.addClause(clause);
    ifs.close();
}

void InferenceDriver::runAStar() {
    Clause start(knowledgeBase.getClauses(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Clause empty(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    knowledgeBase.aStar(start, empty);
}







