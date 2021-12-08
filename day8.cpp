#include <iostream>
#include <fstream>
#include <cstdint>

typedef uint8_t Byte;

struct Signal {
	Byte letters = 0;
	bool solved = false;

	int size() const { return __builtin_popcount(letters); }
	bool unique() const { return size() == 2 || size() == 3 || size() == 4 || size() == 7; }
};

struct Entry {
	Signal signals[10];
	Signal output[4];

	Byte   int_to_sig[10];
	int    sig_to_int[128];

	int num_unique_outputs() const {
		int total = 0;
		for (const Signal& out : output)
			total += out.unique();
		return total;
	}

	void deciphered(Signal& sig, int out) {
		sig_to_int[sig.letters] = out;
		int_to_sig[out] = sig.letters;
		sig.solved = true;
	}

	int solve() const {
		return 1000 * sig_to_int[output[0].letters]
			+   100 * sig_to_int[output[1].letters]
			+    10 * sig_to_int[output[2].letters]
			+     1 * sig_to_int[output[3].letters];
	}

	Entry& decode() {
		for (Signal& sig : signals)
			if (sig.size() == 2)
				deciphered(sig, 1);
			else if (sig.size() == 3)
				deciphered(sig, 7);
			else if (sig.size() == 4)
				deciphered(sig, 4);
			else if (sig.size() == 7)
				deciphered(sig, 8);

		for (Signal& sig : signals) {
			if (sig.size() == 5) {
				if (__builtin_popcount(sig.letters & int_to_sig[7]) == 3)
					deciphered(sig, 3);
				else if (__builtin_popcount(sig.letters & int_to_sig[4]) == 2)
					deciphered(sig, 2);
			}
		}

		for (Signal& sig : signals)
			if (sig.size() == 5 && !sig.solved)
				deciphered(sig, 5);

		for (Signal& sig : signals) {
			if (sig.size() == 6) {
				if (__builtin_popcount(sig.letters & int_to_sig[1]) == 1)
					deciphered(sig, 6);
				else if (__builtin_popcount(sig.letters & int_to_sig[4]) == 4)
					deciphered(sig, 9);
			}
		}

		for (Signal& sig : signals)
			if (sig.size() == 6 && !sig.solved)
				deciphered(sig, 0);

		return *this;
	}
};

std::istream& operator>>(std::istream& is, Signal& signal) {
	std::string str;
	is >> str;
	for (char c : str)
		signal.letters |= (1 << (c - 'a'));
}

std::istream& operator>>(std::istream& is, Entry& entry) {
	for (Signal& sig : entry.signals)
		is >> sig;

	char bar = '|';
	is >> bar;

	for (Signal& out : entry.output)
		is >> out;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Signal& signal) {
	for (int i = 0; i < 8; i++)
		if (signal.letters & (1 << i))
			os << char(i + 'a');

	return os;
}

std::ostream& operator<<(std::ostream& os, const Entry& entry) {
	for (const Signal& sig : entry.signals)
		os << sig << " ";

	os << "|";

	for (const Signal& out : entry.output)
		os << " " << out;
	
	return os;
}

Entry entries[200];

int part1() {
	int total = 0;
	for (const Entry& entry : entries)
		total += entry.num_unique_outputs();
	return total;
}

int part2() {
	int total = 0;
	for (Entry& entry : entries)
		total += entry.decode().solve();
	return total;
}

int main() {
	std::ifstream input("in8.txt");

	for (Entry& entry : entries)
		input >> entry;

	// for (Entry& entry : entries)
	// 	std::cout << entry << std::endl;

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}