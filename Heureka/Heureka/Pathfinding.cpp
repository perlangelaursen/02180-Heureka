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

void Pathfinding::aStar(Heureka::State& start, Heureka::State& goal) {
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
        current.visited = true;
        for(std::pair<int, std::string> neighbor : current.neighbors) {
            int index = neighbor.first;
            if (states[index].visited) {
                continue;
            }
            tempDistanceFromStart = current.distanceFromStart +
                    current.point.calcEuclideanDistance(states[index].point);
            iterator = std::find(queue.begin(), queue.end(), states[index]);
            if (iterator == queue.end()) {
                updateState(goal, tempDistanceFromStart, current, index);
                queue.push_front(states[index]);
            } else if (tempDistanceFromStart >= states[index].distanceFromStart) {
                continue;
            } else {
                updateState(goal, tempDistanceFromStart, current, index);
                (*iterator).cameFrom = states[index].cameFrom;
                (*iterator).distanceFromStart = states[index].distanceFromStart;
                (*iterator).heuristic_distance = states[index].heuristic_distance;
                (*iterator).updateTotalDistance();
            }
        }
    }
}

void Pathfinding::updateState(const Heureka::State &goal, double tempDistanceFromStart, Heureka::State &current,
                              int index) {
    states[index].cameFrom = getIndex(current);
    states[index].distanceFromStart = tempDistanceFromStart;
    states[index].heuristic_distance = states[index].point.calcEuclideanDistance(goal.point);
    states[index].updateTotalDistance();
}

void Pathfinding::reconstructPath(Heureka::State& goal) {
    std::deque<std::string> path;
    int currentIndex = getIndex(goal);
    int previousIndex;
    std::vector<std::pair<int, std::string>>::iterator iterator;
    while (currentIndex != -1) {
        previousIndex = states[currentIndex].cameFrom;
        iterator = std::find_if(states[previousIndex].neighbors.begin(), states[previousIndex].neighbors.end(),
                                [currentIndex](const std::pair<int, std::string>& element) {
                                    return element.first == currentIndex;
                                });
        currentIndex = previousIndex;
        path.push_front((*iterator).second);
    }
    std::copy(path.begin(), path.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int Pathfinding::checkIfStateExists(Heureka::State state) {
    std::vector<Heureka::State>::iterator iterator = std::find(states.begin(), states.end(), state);
    if(iterator == states.end()) {
        states.push_back(state);
        return (int) states.size() - 1;
    } else {
        return (int) std::distance(states.begin(), iterator);
    }
}

void Pathfinding::aStar(int startIndex, int goalIndex) {
    Heureka::State start = states[startIndex];
    Heureka::State goal = states[goalIndex];
    aStar(start, goal);
}

int Pathfinding::getIndex(Heureka::State& state) {
    std::vector<Heureka::State>::iterator iterator = std::find(states.begin(), states.end(), state);
    if(iterator != states.end()) {
        return (int) std::distance(states.begin(), iterator);
    }
    return -1;
}






