#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

int main(int argc,char *argv[]) {
	std::vector<std::string> temp(5);
	std::string tempString;
	std::ifstream ifs(argv[1]);
	if(!(ifs.is_open())) {
		std::cerr <<  "Error! Could not open file";
	}

	while (std::getline(ifs, tempString)) {
		boost::split(temp, tempString, boost::is_any_of(" "));
	}

	ifs.close();

	std::cout << "Hello World\n";
	return 0;
}