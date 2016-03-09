#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc,char *argv[]) {
	std::vector<std::string> temp(5);
	std::string tempString;
	std::string file = argv[1];
	std::ifstream ifs(file);
	std::istringstream istringstream(tempString);
	int n=0;
	if(!(ifs.is_open())) {
		std::cerr <<  "Error! Could not open file";
	}

	while (std::getline(ifs, tempString)) {
		for (std::istream_iterator<std::string> iterator = std::istream_iterator<std::string>(istringstream);
			 iterator != std::istream_iterator<std::string>() && n < 5; ++iterator, ++n) {
			temp[n] = *iterator;
		}
	}

	ifs.close();

	std::cout << "Hello World\n";
		return 0;
}