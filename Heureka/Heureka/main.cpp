#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Pathfinding.h"

int main(int argc,char *argv[]) {
	std::vector<std::string> temp(5);
	std::string tempString;
	std::string file = argv[1];
	std::ifstream ifs(file);
	std::istringstream istringstream(tempString);
	std::string::size_type sz;

	int n=0;
	int tempX1, tempY1, tempX2, tempY2;
	if(!(ifs.is_open())) {
		std::cerr <<  "Error! Could not open file";
	}

	while (std::getline(ifs, tempString)) {
		for (std::istream_iterator<std::string> iterator = std::istream_iterator<std::string>(istringstream);
			 iterator != std::istream_iterator<std::string>() && n < 5; ++iterator, ++n) {
			temp[n] = *iterator;
		}
		tempX1 = std::stoi(temp[0], &sz);
		tempY1 = std::stoi(temp[1], &sz);
		tempX2 = std::stoi(temp[3], &sz);
		tempY2 = std::stoi(temp[4], &sz);
		Pathfinding::addState(tempX1, tempY1, temp[2], tempX2, tempY2);
		temp.clear();
		temp.resize(5);
	}

	Heureka::Point point1(tempX1, tempY1);
	Heureka::Point point2(tempY1, tempY2);
	Pathfinding::aStar(point1, point2);


	ifs.close();

	std::cout << "Hello World\n";
		return 0;
}