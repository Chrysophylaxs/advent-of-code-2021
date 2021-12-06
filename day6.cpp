#include <iostream>
#include <fstream>

typedef unsigned long long Ull;
Ull lookup[257][9] = {0};

Ull spawn(int fish, int days) {
	if (lookup[days][fish])
		return lookup[days][fish];

	if (fish == 0)
		lookup[days][fish] = spawn(6, days - 1) + spawn(8, days - 1);
	else
		lookup[days][fish] = spawn(fish - 1, days - 1);

	return lookup[days][fish];
}

int lantern_fish[300];

Ull part1() {
	Ull total = 0;
	for (const int& lf : lantern_fish)
		total += spawn(lf, 80);

	return total;
}

Ull part2() {
	Ull total = 0;
	for (const int& lf : lantern_fish)
		total += spawn(lf, 256);

	return total;
}

int main() {
	std::ifstream input("in6.txt");

	char comma;
	for (int i = 0; i < 299; i++)
		input >> lantern_fish[i] >> comma;
	input >> lantern_fish[299];

	for (int fish = 0; fish < 9; fish++)
		lookup[0][fish] = 1;

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}