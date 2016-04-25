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

Literal InferenceDriver::readEntailed() {
    std::string tempString;
    std::ifstream ifs(entailed);

    if(!(ifs.is_open())) {
        std::cerr << "Error! Could not open the file" + entailed;
    }

    getline(ifs, tempString);
    Literal literal(tempString);
    literal.negated = !literal.negated;
    ifs.close();
    return literal;
}

void InferenceDriver::runAStar() {
    Clause start(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Literal entailed = readEntailed();
    start.addLiteralToClause(entailed);
    knowledgeBase.addClause(start);
    int startIndex =boost::lexical_cast<int>(knowledgeBase.getClauses().size() -1);

    Clause empty(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Literal emptyLiteral("");
    empty.addLiteralToClause(emptyLiteral);

    knowledgeBase.aStar(startIndex, empty);
}