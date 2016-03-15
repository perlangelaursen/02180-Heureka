#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

int main() {
	std::vector<std::string> temp(5);
	std::string tempString;
	std::string file = "Copenhagen.txt";
	std::ifstream ifs(file);

	int tempX1, tempX2, tempY1, tempY2;

	if(!(ifs.is_open())) {
		std::cerr <<  "Error! Could not open file";
	}

	while (std::getline(ifs, tempString)) {
		boost::split(temp, tempString, boost::is_any_of(" "));
		tempX1 = boost::lexical_cast<int>(temp[0]);
		tempY1 = boost::lexical_cast<int>(temp[1]);
		tempX2 = boost::lexical_cast<int>(temp[3]);
		tempY2 = boost::lexical_cast<int>(temp[4]);

		std::cout << tempX1 << " " << tempY1 << " " << " " << temp[2] << " " << tempX2 << " " << tempY2 << std::endl;
	}


	std::cout << "Hello, World!" << endl;
	return 0;
}