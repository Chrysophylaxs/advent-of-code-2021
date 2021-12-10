#include <iostream>
#include <fstream>
#include <algorithm>

int numbers[1000];

int fuel_cost(int x) {
	int tot = 0;
	for (int i : numbers)
		tot += std::abs(x - i);

	return tot;
}

int fuel_cost_crab(int x) {
	int tot = 0;
	for (int i : numbers) {
		int len = std::abs(x - i);
		tot += len * (len + 1) / 2;
	}

	return tot;
}

int part1() {
	int best = 1000000000;

	for (int x = 0; x < 2000; x++)
		best = std::min(fuel_cost(x), best);

	return best;
}

int part2() {
	int best = 1000000000;

	for (int x = 0; x < 2000; x++)
		best = std::min(fuel_cost_crab(x), best);

	return best;
}

int main() {
	std::ifstream input("in7.txt");

	char comma;
	for (int i = 0; i < 999; i++)
		input >> numbers[i] >> comma;
	input >> numbers[999];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}
