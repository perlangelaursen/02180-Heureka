#include <iostream>
#include "PathfindingDriver.h"
#include "InferenceDriver.h"

using namespace std;

int main(int argc, char *argv[]) {
	PathfindingDriver driver;
	InferenceDriver inferenceDriver;
	if(argc == 2) {
		if(strcmp(argv[1], "pathfinding") == 0) {
			driver.run();
		} else if (strcmp(argv[1], "inference") == 0) {
			inferenceDriver.run();
		} else {
			std::cout << "Please specify arguments\n";
			std::cout << "\t 1. pathfinding\n";
			std::cout << "\t 2. inference";
		}
	} else {
		driver.run();
		inferenceDriver.run();
	}

	return 0;
}