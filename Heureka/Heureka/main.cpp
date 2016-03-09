#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void readFromFile(std::string file);

int main(int argc, char *argv[]) {
	std::string file = argv[1];
	//readFromFile("Copenhagen.txt");
	std::vector<std::string> temp(5);
	std::string tempString;
	std::ifstream ifs(file);
	std::istringstream sstream(tempString);
	int n = 0;
	if(!(ifs.is_open())) {
		std::cerr << "Error! Could not open file";
	}

	while (getline(ifs, tempString)) {
		for (std::istream_iterator<std::string> iterator = std::istream_iterator<std::string>(sstream);
			 iterator != std::istream_iterator<std::string>() && n < 5; ++iterator, ++n) {
			temp[n] = *iterator;
		}


	}

	ifs.close();

	std::cout << "Hello World\n";
	return 0;
}

void readFromFile(std::string file) {
	std::vector<std::string> temp(5);
	std::string tempString;
	std::ifstream ifs(file);
	std::istringstream sstream(tempString);
	int n = 0;
	if(!(ifs.is_open())) {
		std::cerr << "Error! Could not open file";
	}

	while (getline(ifs, tempString)) {
		for (std::istream_iterator<std::string> iterator = std::istream_iterator<std::string>(sstream);
			 iterator != std::istream_iterator<std::string>() && n < 5; ++iterator, ++n) {
			temp[n] = *iterator;
		}


	}

	ifs.close();
}