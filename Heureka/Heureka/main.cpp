#include <iostream>
#include "PathfindingDriver.h"
#include "InferenceDriver.h"

using namespace std;

int main() {
	PathfindingDriver driver;
	driver.run();

	InferenceDriver inferenceDriver;
	inferenceDriver.run();
	return 0;
}