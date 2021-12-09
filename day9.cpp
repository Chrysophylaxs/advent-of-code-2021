#include <iostream>
#include <fstream>

char grid[102][102];

int part1() {
	int tot = 0;

	for (int i = 1; i < 101; i++)
		for (int j = 1; j < 101; j++)
			if (grid[i][j] < grid[i-1][j] && grid[i][j] < grid[i+1][j] && grid[i][j] < grid[i][j-1] && grid[i][j] < grid[i][j+1])
				tot += grid[i][j] - '0' + 1;

	return tot;
}

bool visited[100][100] = {false};

int size(int i, int j) {
	if (visited[i][j] || grid[i][j] == '9')
		return 0;
	
	visited[i][j] = true;
	return size(i-1, j) + size(i+1, j) + size(i, j-1) + size(i, j+1) + 1;
}

int part2() {
	int one = 0, two = 0, three = 0;
	for (int i = 1; i < 101; i++) {
		for (int j = 1; j < 101; j++) {
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

	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
			grid[i][j] = '9';

	for (int i = 1; i < 101; i++)
		for (int j = 1; j < 101; j++)
			input >> grid[i][j];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}