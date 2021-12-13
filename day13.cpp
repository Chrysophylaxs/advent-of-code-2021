#include <iostream>
#include <fstream>

struct Paper {
	Paper& fold_x(int x) {
		for (int i = 1; x + i < width && x - i >= 0; i++)
			for (int j = 0; j < height; j++)
				dots[x - i][j] |= dots[x + i][j];

		width = x;
		return *this;
	}

	Paper& fold_y(int y) {
		for (int j = 1; y + j < height && y - j >= 0; j++)
			for (int i = 0; i < width; i++)
				dots[i][y - j] |= dots[i][y + j];

		height = y;
		return *this;
	}

	int num_dots() const {
		int tot = 0;
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				tot += dots[i][j];

		return tot;
	}

	int width = 1311, height = 894;
	bool dots[1311][894] = {false};
};

std::ostream& operator<<(std::ostream& os, const Paper& p) {
	for (int j = 0; j < p.height; j++) {
		for (int i = 0; i < p.width; i++)
			os << (p.dots[i][j] ? "#" : ".");
		os << std::endl;
	}
	return os;
}

Paper paper;

int part1() { return paper.fold_x(655).num_dots(); }

int part2() {
	paper.fold_y(447).fold_x(327).fold_y(223).fold_x(163)
		.fold_y(111).fold_x(81).fold_y(55).fold_x(40)
		.fold_y(27).fold_y(13).fold_y(6);
	return 0;
}

int main() {
	std::ifstream input("in13.txt");

	char comma;
	int x, y;

	for (int i = 0; i < 952; i++) {
		input >> x >> comma >> y;
		paper.dots[x][y] = true;
	}

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	std::cout << paper << std::endl;

	return 0;
}