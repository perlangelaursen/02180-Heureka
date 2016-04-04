//
// Created by Per Lange Laursen on 08/03/16.
//

#include "Pathfinding.h"

void Pathfinding::addState(int x1, int y1, std::string roadName, int x2, int y2) {
    Heureka::Point point1(x1, y1);
    Heureka::State temp1(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), point1);

    Heureka::Point point2(x2, y2);
    Heureka::State temp2(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), point2);;

    int index1 = checkIfStateExists(temp1);
    int index2 = checkIfStateExists(temp2);
    states[index1].neighbors.push_back(std::make_pair(index2, roadName));
}

void Pathfinding::aStar(int start, int goal) {
    states[start].distanceFromStart = 0;
    states[start].heuristic_distance = states[start].point.calcEuclideanDistance(states[goal].point);
    states[start].updateTotalDistance();
    queue.push_back(states[start]);
    double tempDistanceFromStart;
    std::deque<Heureka::State>::iterator iterator;

    while (!queue.empty()) {
        std::sort(queue.begin(), queue.end());
        int currentIndex = getIndex(queue.front());
        if (currentIndex == goal) {
            reconstructPath(start, goal);
            queue.clear();
            break;
        }
        queue.pop_front();
        states[currentIndex].visited = true;
        for(auto neighbor : states[currentIndex].neighbors) {
            int index = neighbor.first;
            if (states[index].visited) {
                continue;
            }
            tempDistanceFromStart = states[currentIndex].distanceFromStart +
                    states[currentIndex].point.calcEuclideanDistance(states[index].point);
            iterator = std::find(queue.begin(), queue.end(), states[index]);
            if (iterator == queue.end()) {
                updateState(states[goal], tempDistanceFromStart, currentIndex, index);
                queue.push_front(states[index]);
            } else if (tempDistanceFromStart >= states[index].distanceFromStart) {
                continue;
            } else {
                updateState(states[goal], tempDistanceFromStart, currentIndex, index);
                iterator -> cameFrom = states[index].cameFrom;
                iterator -> distanceFromStart = states[index].distanceFromStart;
                iterator -> heuristic_distance = states[index].heuristic_distance;
                iterator -> updateTotalDistance();
            }
        }
    }
}

void Pathfinding::updateState(const Heureka::State &goal, double tempDistanceFromStart, int current,
                              int index) {
    states[index].cameFrom = current;
    states[index].distanceFromStart = tempDistanceFromStart;
    states[index].heuristic_distance = states[index].point.calcEuclideanDistance(goal.point);
    states[index].updateTotalDistance();
}

void Pathfinding::reconstructPath(int start, int goal) {
    std::deque<std::string> path;
    int currentIndex = goal;
    int previousIndex;
    std::vector<std::pair<int, std::string>>::iterator iterator;
    while (currentIndex != start) {
        previousIndex = states[currentIndex].cameFrom;
        iterator = std::find_if(states[previousIndex].neighbors.begin(), states[previousIndex].neighbors.end(),
                                [currentIndex](const std::pair<int, std::string> element) {
                                    return element.first == currentIndex;
                                });

        currentIndex = previousIndex;
        path.push_front(iterator -> second);
    }
    for(auto s : path) {
        std::cout << s << "\n";
    }
}

int Pathfinding::checkIfStateExists(Heureka::State state) {
    auto iterator = std::find(states.begin(), states.end(), state);
    if(iterator == states.end()) {
        states.push_back(state);
        return boost::lexical_cast<int>(states.size()-1);
    } else {
        return boost::lexical_cast<int>(std::distance(states.begin(), iterator));
    }
}

int Pathfinding::getIndex(Heureka::State& state) {
    auto iterator = std::find(states.begin(), states.end(), state);
    if(iterator != states.end()) {
        return boost::lexical_cast<int>(std::distance(states.begin(), iterator));
    }
    return -1;
}

int Pathfinding::getIndex(int x, int y) {
    Heureka::Point temp(x, y);
    auto iterator = std::find_if(states.begin(), states.end(), [temp](const Heureka::State& state) {
        return state.point == temp;
    });
    return boost::lexical_cast<int>(std::distance(states.begin(), iterator));
}








