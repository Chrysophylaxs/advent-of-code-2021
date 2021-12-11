#include <iostream>
#include <fstream>

const int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

class Octopus {
public:
	int charge() {
		energy += 1;
		
		if (!edge && ready())
			return flash();
		else
			return 0;
	}
	
	int flash() {
		flashed = true;

		int tot = 1;
		for (Octopus* oct : neighbors)
			tot += oct->charge();
		return tot;
	}

	bool ready() const { return !flashed && energy > 9; }
	void reset() { if (flashed) flashed = false, energy = 0; }

	friend class Cavern;
	friend std::istream& operator>>(std::istream& is, Octopus& oct);
	friend std::ostream& operator<<(std::ostream& os, const Octopus& oct);

private:
	Octopus* neighbors[8] = {0};
	int energy = 0;
	bool flashed = false;
	bool edge = true;
};

class Cavern {
public:
	Cavern() {
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
				for (int n = 0; n < 8; n++)
					grid[i][j].neighbors[n] = &grid[i + dirs[n][0]][j + dirs[n][1]], grid[i][j].edge = false;
	}

	int step() {
		int flashes = charge();
		reset();
		return flashes;
	}

	friend std::istream& operator>>(std::istream& is, Cavern& cav);
	friend std::ostream& operator<<(std::ostream& os, const Cavern& cav);

private:
	int charge() {
		int tot = 0;
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
				tot += grid[i][j].charge();
		return tot;
	}

	void reset() {
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
				grid[i][j].reset();
	}

	Octopus grid[12][12];
};

std::istream& operator>>(std::istream& is, Octopus& oct) { char c; is >> c; oct.energy = c - '0'; return is; }

std::istream& operator>>(std::istream& is, Cavern& cav) {
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
			is >> cav.grid[i][j];
	return is;
}

std::ostream& operator<<(std::ostream& os, const Octopus& oct) { return os << oct.energy; }

std::ostream& operator<<(std::ostream& os, const Cavern& cav) {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++)
			os << cav.grid[i][j];
		os << std::endl;
	}
	return os;
}

int part1() {
	std::ifstream input("in11.txt");
	Cavern cavern;

	input >> cavern;
	int tot = 0;

	for (int i = 0; i < 100; i++)
		tot += cavern.step();
	return tot;
}

int part2() {
	std::ifstream input("in11.txt");
	Cavern cavern;

	input >> cavern;

	for (int i = 1;; i++)
		if (cavern.step() == 100) 
			return i;
}

int main() {
	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}