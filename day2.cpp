#include <iostream>
#include <fstream>

std::string directions[1000];
int values[1000];

int part1() {
	int hor = 0;
	int ver = 0;

	for (int i = 0; i < 1000; i++)
		if (directions[i] == "forward")
			hor += values[i];
		else if (directions[i] == "down")
			ver += values[i];
		else if (directions[i] == "up")
			ver -= values[i];

	return hor * ver;
}

int part2() {
	int hor = 0;
	int ver = 0;
	int aim = 0;

	for (int i = 0; i < 1000; i++)
		if (directions[i] == "forward") {
			hor += values[i];
			ver += aim * values[i];
		}
		else if (directions[i] == "down")
			aim += values[i];
		else if (directions[i] == "up")
			aim -= values[i];

	return hor * ver;
}

int main() {
	std::ifstream input("in2.txt");

	for (int i = 0; i < 1000; i++)
		input >> directions[i] >> values[i];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}