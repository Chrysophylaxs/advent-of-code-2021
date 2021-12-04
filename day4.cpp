#include <iostream>
#include <fstream>

class Bingo {
public:
	friend std::istream& operator>>(std::istream& is, Bingo& bingo);
	friend std::ostream& operator<<(std::ostream& os, const Bingo& bingo);

	bool winner() const {
		for (int i = 0; i < 5; i++) {
			bool hor = true, ver = true;
			for (int j = 0; j < 5; j++) {
				if (!marked[i][j])
					hor = false;
				if (!marked[j][i])
					ver = false;
			}
			
			if (hor || ver)
				return true;
		}

		return false;
	}

	bool play(int num) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (board[i][j] == num)
					marked[i][j] = true;

		return winner();
	}

	int sum_unmarked() const {
		int sum = 0;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (!marked[i][j])
					sum += board[i][j];

		return sum;
	}

private:
	int board[5][5] = {0};
	bool marked[5][5] = {0};
};

int numbers[100];
Bingo bingos[100];

std::istream& operator>>(std::istream& is, Bingo& bingo) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			is >> bingo.board[i][j];
	return is;
}

std::ostream& operator<<(std::ostream& os, const Bingo& bingo) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			os << (bingo.marked[i][j] ? "[" : " ") << (bingo.board[i][j] < 10 ? " " : "") << bingo.board[i][j] << (bingo.marked[i][j] ? "]" : " " ) << " ";
		std::cout << std::endl;
	}
	return os;
}

int part1() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (bingos[j].play(numbers[i])) {
				std::cout << "Turn: " << i << std::endl << bingos[j];
				return numbers[i] * bingos[j].sum_unmarked();
			}
	return -1;
}

int part2() {
	int tot = 0;
	bool winners[100] = {false};
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (!winners[j] && bingos[j].play(numbers[i])) {
				winners[j] = true;
				tot++;
			}

			if (tot == 100) {
				std::cout << "Turn: " << i << std::endl << bingos[j];
				return numbers[i] * bingos[j].sum_unmarked();
			}
		}
	}

	return -1;
}

int main() {
	std::ifstream input("in4.txt");

	char comma;
	for (int i = 0; i < 99; i++)
		input >> numbers[i] >> comma;
	input >> numbers[99];

	for (int i = 0; i < 100; i++)
		input >> bingos[i];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}