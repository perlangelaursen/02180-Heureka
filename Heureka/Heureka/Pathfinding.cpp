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
    start.updateTotalDistance();
    queue.push_back(start);
    double tempDistanceFromStart;
    std::deque<Heureka::State>::iterator iterator;

    while (!queue.empty()) {
        std::sort(queue.begin(), queue.end());
        Heureka::State current = queue.front();
        if (current == goal) {
            reconstructPath(goal);
            queue.clear();
            break;
        }
        queue.pop_front();
        for(std::pair<int, std::string> neighbor : current.neighbors) {
            int index = neighbor.first;
            if (states[index].visited) {
                continue;
            }
            states[index].visited = true;
            tempDistanceFromStart = current.distanceFromStart +
                    current.point.calcEuclideanDistance(states[index].point);
            if (tempDistanceFromStart >= states[index].distanceFromStart) {
                continue;
            }
            states[index].cameFrom = getIndex(current);
            states[index].distanceFromStart = tempDistanceFromStart;
            states[index].heuristic_distance = states[index].point.calcEuclideanDistance(goal.point);
            states[index].updateTotalDistance();
            iterator = std::find(queue.begin(), queue.end(), states[index]);
            if(iterator != queue.end()) {
                (*iterator).cameFrom = states[index].cameFrom;
                (*iterator).distanceFromStart = states[index].distanceFromStart;
                (*iterator).heuristic_distance = states[index].heuristic_distance;
                (*iterator).updateTotalDistance();
            } else {
                queue.push_front(states[index]);
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
        currentIndex = goal.cameFrom;
        path.insert(path.begin(), (*iterator).second);
    }
    std::copy(path.begin(), path.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int Pathfinding::checkIfStateExists(Heureka::State state) {
    int i = 0;
    for(auto& s : states) {
        if (s == state) return i;
        ++i;
    }
    states.push_back(state);
    return (int) states.size();
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






