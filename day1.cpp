#include <iostream>
#include <fstream>

int numbers[2000];

int part1() {
	int tot = 0;

	for (int i = 0; i < 1999; i++)
		if (numbers[i] < numbers[i + 1])
			tot += 1;

	return tot;
}

int part2() {
	int tot = 0;

	for (int i = 0; i < 1997; i++)
		if (numbers[i] + numbers[i + 1] + numbers[i + 2] < numbers[i + 1] + numbers[i + 2] + numbers[i + 3])
			tot += 1;

	return tot;
}

int main() {
	std::ifstream input("in1.txt");

	for (int i = 0; i < 2000; i++)
		input >> numbers[i];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}