#include <iostream>
#include <fstream>

std::string numbers[1000];
bool mask[1000];

int part1() {
	int ones[12];
	for (int i = 0; i < 12; i++)
		ones[i] = 0;

	for (int i = 0; i < 12; i++)
		for (int n = 0; n < 1000; n++)
			ones[i] += numbers[n][i] - '0';

	int gamma = 0;
	for (int i = 0; i < 12; i++)
		if (ones[11 - i] > 500)
			gamma |= (1 << i);

	int epsilon = ~gamma & ((1 << 12) - 1);

	// std::cout << "Gamma: " << gamma << std::endl;
	// std::cout << "Epsilon: " << epsilon << std::endl;
	return gamma * epsilon;
}

int remove(int n, char c) {
	int removed = 0;
	
	for (int i = 0; i < 1000; i++)
		if (mask[i] && numbers[i][n] == c)
			mask[i] = false, removed++;

	// std::cout << "Removed: " << removed << " " << c << std::endl;
	return removed;
}

template<bool oxygen>
int run() {
	for (int i = 0; i < 1000; i++)
		mask[i] = true;

	int remaining = 1000;
	for (int n = 0; n < 12 && remaining > 1; n++) {
		int ones = 0;
		for (int i = 0; i < 1000; i++)
			if (mask[i])
				ones += numbers[i][n] - '0';

		int zeros = remaining - ones;

		// std::cout << "Ones/Remaining: " << ones << "/" << remaining << std::endl;

		remaining -= remove(n, '0' + (oxygen ? ones < zeros : ones >= zeros));
	}

	for (int i = 0; i < 1000; i++)
		if (mask[i])
			return std::stoi(numbers[i], nullptr, 2);

	return 0;
}

int part2() {
	int oxygen = run<true>();
	int co2 = run<false>();
	
	// std::cout << "Oxygen: " << oxygen << std::endl;
	// std::cout << "CO2: " << co2 << std::endl;
	return oxygen * co2;
}

int main() {
	std::ifstream input("in3.txt");

	for (int i = 0; i < 1000; i++)
		input >> numbers[i];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}