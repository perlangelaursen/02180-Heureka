//
// Created by Per Lange Laursen on 12/04/16.
//

#include "Clause.h"

void Clause::updateTotalDistance() {
    totalDistance = distanceFromStart + heuristic_distance;
}

void Clause::addToChildKnowledgeBase(const std::vector<Clause> &local) {
    std::vector<Clause>::const_iterator iterator;
    for(iterator = local.begin(); iterator != local.end(); ++iterator) {
        childKnowledgeBase.push_back(*iterator);
    }
    childKnowledgeBase.push_back(*this);
}

void Clause::addLiteralToClause(Literal &literal) {
    symbols.push_front(literal);
}

void Clause::calcHeuristicDistance() {
    heuristic_distance = boost::lexical_cast<double>(symbols.size());
}

std::string Clause::toString() const {
    std::string out("");
    for(auto literal : symbols) {
        out += literal.toString();
        out += " || ";
    }
    out = (out.compare("") == 0) ? "Ø" : out.substr(0, out.length() - 4);
    if (symbols.size() > 1) out = "(" + out +")";
    return out;
}

bool Clause::operator()(const Clause &lhs, const Clause &rhs) {
    return lhs.totalDistance < rhs.totalDistance;
}

bool Clause::operator<(const Clause &rhs) {
    return totalDistance < rhs.totalDistance;
}

bool Clause::operator==(const Clause &rhs) {
    return symbols.size() == rhs.symbols.size() && symbols == rhs.symbols;
}

bool Clause::operator!=(const Clause &rhs) {
    return symbols != rhs.symbols;
}

std::ostream &operator<<(std::ostream &os, const Clause &clause) {
    os << clause.toString();
    return os;
}

Clause Clause::clausalResolution(Clause &clause) {
    std::deque<Literal> allSymbols;
    std::deque<Literal> resolutedSymbols;
    addLiterals(allSymbols, this->symbols);
    addLiterals(allSymbols, clause.symbols);

    eliminateDuplicates(allSymbols, resolutedSymbols);

    Clause result(this->childKnowledgeBase);
    for(Clause c : childKnowledgeBase) {
        if(result == c) return Clause();
    }
    result.symbols=resolutedSymbols;

    return result;
}

void Clause::eliminateDuplicates(std::deque<Literal> &allSymbols, std::deque<Literal> &resolutedSymbols) const {
    for(Literal l : allSymbols) {
        Literal inverse(l.toString());
        inverse.negated = !inverse.negated;
        if(std::find(allSymbols.begin(), allSymbols.end(), inverse) == allSymbols.end())
            resolutedSymbols.push_back(l);
    }
}


void Clause::addLiterals(std::deque<Literal> &to,
                         std::deque<Literal> &symbols) {
    std::deque<Literal>::const_iterator iterator;
    for(iterator = symbols.begin(); iterator != symbols.end(); ++iterator) {
        to.push_back(*iterator);
    }
}

Clause::Clause() {

}

std::vector<Clause> &Clause::getResolutedClauses() {
    resolutedClauses.clear();
    Clause empty;
    for(Clause clause : childKnowledgeBase) {
        Clause resultClause = clausalResolution(clause);
        if(resultClause != empty) {
            resolutedClauses.push_back(resultClause);
        }
    }
    return resolutedClauses;
}
