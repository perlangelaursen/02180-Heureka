//
// Created by Per Lange Laursen on 08/03/16.
//

#include "Pathfinding.h"

void Pathfinding::addState(int x1, int y1, std::string roadName, int x2, int y2) {
    Heureka::Point point1(x1, y1);
    Heureka::State temp1(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), point1);
    states.push_back(temp1);

    Heureka::Point point2(x2, y2);
    Heureka::State temp2(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), point2);;
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
        openSet.sort();
        Heureka::State current = openSet.front();
        if (current == goal) {
            reconstructPath(goal);
            openSet.clear();
            break;
        }
        openSet.pop_front();
        for(std::pair<int, std::string> neighbor : current.neighbors) {
            int index = neighbor.first;
            if (states[index].visited) {
                continue;
            }
            tempDistanceFromStart = current.distanceFromStart +
                    current.point.calcEuclideanDistance(states[index].point);
            if (tempDistanceFromStart >= states[index].distanceFromStart) {
                continue;
            }
            states[index].cameFrom = getIndex(current);
            states[index].distanceFromStart = tempDistanceFromStart;
            states[index].heuristic_distance = states[index].point.calcEuclideanDistance(goal.point);
            states[index].updateTotalDistance();
            iterator = std::find(openSet.begin(), openSet.end(), states[index]);
            if(iterator != openSet.end()) {
                (*iterator).cameFrom = states[index].cameFrom;
                (*iterator).distanceFromStart = states[index].distanceFromStart;
                (*iterator).heuristic_distance = states[index].heuristic_distance;
                (*iterator).updateTotalDistance();
            } else {
                openSet.push_front(states[index]);
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
                                [goal](const std::pair<int, std::string>& element) {
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
    for(auto& s : states) {
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
    for(auto& state : states) {
        if (state == s) return i;
        ++i;
    }
    return -1;
}






