#include <iostream>
#include <fstream>

char grid[100][100];

int part1() {
	int tot = 0;

	if (grid[0][0] < grid[0][1] && grid[0][0] < grid[1][0])
		tot += grid[0][0] - '0' + 1;

	if (grid[99][0] < grid[99][1] && grid[99][0] < grid[98][0])
		tot += grid[0][0] - '0' + 1;

	if (grid[0][99] < grid[1][99] && grid[0][99] < grid[0][98])
		tot += grid[0][0] - '0' + 1;

	if (grid[99][99] < grid[99][98] && grid[99][99] < grid[98][99])
		tot += grid[0][0] - '0' + 1;

	for (int i = 1; i < 99; i++) {
		if (grid[i][0] < grid[i-1][0] && grid[i][0] < grid[i+1][0] && grid[i][0] < grid[i][1])
			tot += grid[i][0] - '0' + 1;
		if (grid[i][99] < grid[i-1][99] && grid[i][99] < grid[i+1][99] && grid[i][99] < grid[i][98])
			tot += grid[i][99] - '0' + 1;
	}

	for (int j = 1; j < 99; j++) {
		if (grid[0][j] < grid[0][j-1] && grid[0][j] < grid[0][j+1] && grid[0][j] < grid[1][j])
			tot += grid[0][j] - '0' + 1;
		if (grid[99][j] < grid[99][j-1] && grid[99][j] < grid[99][j+1] && grid[99][j] < grid[98][j])
			tot += grid[99][j] - '0' + 1;
	}

	for (int i = 1; i < 99; i++)
		for (int j = 1; j < 99; j++)
			if (grid[i][j] < grid[i-1][j] && grid[i][j] < grid[i+1][j] && grid[i][j] < grid[i][j-1] && grid[i][j] < grid[i][j+1])
				tot += grid[i][j] - '0' + 1;

	return tot;
}

bool visited[100][100] = {false};

int size(int i, int j) {
	if (i < 0 || i > 99 || j < 0 || j > 99 || visited[i][j] || grid[i][j] == '9')
		return 0;
	
	visited[i][j] = true;
	return size(i-1, j) + size(i+1, j) + size(i, j-1) + size(i, j+1) + 1;
}

int part2() {
	int one = 0, two = 0, three = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int basin = size(i, j);

			if (basin > one) {
				three = two;
				two = one;
				one = basin;
			}
			else if (basin > two) {
				three = two;
				two = basin;
			}
			else if (basin > three)
				three = basin;
		}
	}
	return one * two * three;
}

int main() {
	std::ifstream input("in9.txt");

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			input >> grid[i][j];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}