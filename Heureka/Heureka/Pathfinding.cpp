//
// Created by Per Lange Laursen on 08/03/16.
//

#include "Pathfinding.h"

void Pathfinding::addState(int x1, int y1, std::string roadName, int x2, int y2) {
    Heureka::Point point1(x1, y1);
    Heureka::State temp1;
    temp1.point = point1;
    temp1.distanceFromStart = std::numeric_limits<double>::max();
    temp1.heuristic_distance = std::numeric_limits<double>::max();
    states.push_back(temp1);

    Heureka::Point point2(x2, y2);
    Heureka::State temp2;
    temp2.point = point2;
    temp2.distanceFromStart = std::numeric_limits<double>::max();
    temp2.heuristic_distance = std::numeric_limits<double>::max();
    states.push_back(temp2);

    int index1 = checkIfStateExists(temp1);
    int index2 = checkIfStateExists(temp2);
    states[index1].neighbors.push_back(std::make_pair(index2, roadName));
}

void Pathfinding::aStar(Heureka::State start, Heureka::State goal) {
    start.distanceFromStart = 0;
    start.heuristic_distance = start.point.calcEuclideanDistance(goal.point);
    openSet.push_back(start);
    double tempDistanceFromStart;
    std::list<Heureka::State>::iterator iterator;

    while (!openSet.empty()) {
        std::sort(openSet.begin(), openSet.end());
        Heureka::State current = openSet.front();
        if (current == goal) {
            reconstructPath(goal);
            openSet.clear();
            break;
        }
        openSet.pop_front();
        for(std::pair<int, std::string> neighbor : current.neighbors) {
            if (states[neighbor.first].visited) {
                continue;
            }
            tempDistanceFromStart = current.distanceFromStart +
                    current.point.calcEuclideanDistance(states[neighbor.first].point);
            if (tempDistanceFromStart >= states[neighbor.first].distanceFromStart) {
                continue;
            }
            states[neighbor.first].cameFrom = getIndex(current);
            states[neighbor.first].distanceFromStart = tempDistanceFromStart;
            states[neighbor.first].heuristic_distance = states[neighbor.first].point.calcEuclideanDistance(goal.point);
            iterator = std::find_if(openSet.begin(), openSet.end(), [](Heureka::State& state) {
                return state.point == states[neighbor.first].point;
            });
            if(iterator != openSet.end()) {
                (*iterator).cameFrom = states[neighbor.first].cameFrom;
                (*iterator).distanceFromStart = states[neighbor.first].distanceFromStart;
                (*iterator).heuristic_distance = states[neighbor.first].heuristic_distance;
            } else {
                openSet.push_front(states[neighbor.first]);
            }
        }
    }
}

void Pathfinding::reconstructPath(Heureka::State goal) {
    std::vector<std::string> path;
    int currentIndex = getIndex(goal);
    std::vector<std::pair<int, std::string>>::iterator iterator;
    while (currentIndex != -1) {
        iterator = std::find_if(goal.neighbors.begin(), goal.neighbors.end(),
                                [](const std::pair<int, std::string>& element) {
                                    return element.first == goal.cameFrom;
                                });
        currentIndex = (*iterator).first;
        path.insert(path.begin(), (*iterator).second);
    }
    std::copy(path.begin(), path.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int Pathfinding::checkIfStateExists(Heureka::State state) {
    bool inSet = false;
    int i = 0;
    for(Heureka::State s : states) {
        if(state == s) {
            inSet = true;
        }
    }
    if(!inSet) {
        states.push_back(state);
        i = (int) (states.size() - 1);
    }
    return i;
}

void Pathfinding::aStar(int startIndex, int goalIndex) {
    Heureka::State start = states[startIndex];
    Heureka::State goal = states[goalIndex];
    aStar(start, goal);
}

int Pathfinding::getIndex(Heureka::State s) {
    int i = 0;
    for(auto state : states) {
        if (state == s) return i;
        ++i;
    }
    return -1;
}






