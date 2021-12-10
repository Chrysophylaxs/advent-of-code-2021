#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

typedef unsigned long long Ull;

Ull cost[128];
Ull cost2[128];
bool type[128];
char comp[128];

std::string lines[90];

Ull check_corrupted(const std::string& line) {
	std::vector<char> stack;
	for (char c : line)
		if (type[c])
			stack.push_back(c);
		else if (stack.empty())
			return 0;
		else if (stack.back() == comp[c])
			stack.pop_back();
		else
			return cost[c];

	return 0;
}

Ull check_incomplete(const std::string& line) {
	std::vector<char> stack;
	for (char c : line)
		if (type[c])
			stack.push_back(c);
		else if (stack.empty())
			return 0;
		else if (stack.back() == comp[c])
			stack.pop_back();
		else
			return 0;

	Ull tot = 0;
	for (auto it = stack.crbegin(); it != stack.crend(); it++)
		tot *= 5, tot += cost2[comp[*it]];

	return tot;
}


Ull part1() {
	Ull tot = 0;
	for (const std::string& line : lines)
		tot += check_corrupted(line);

	return tot;	
}

Ull part2() {
	std::vector<Ull> incomplete;
	for (const std::string& line : lines) {
		Ull x = check_incomplete(line);
		if (x)
			incomplete.push_back(x);
	}

	std::sort(incomplete.begin(), incomplete.end());
	return incomplete[incomplete.size() / 2];
}

int main() {
	std::ifstream input("in10.txt");

	for (std::string& line : lines)
		input >> line;

	cost[')'] = 3;
	cost[']'] = 57;
	cost['}'] = 1197;
	cost['>'] = 25137;

	cost2[')'] = 1;
	cost2[']'] = 2;
	cost2['}'] = 3;
	cost2['>'] = 4;

	comp['('] = ')';
	comp['['] = ']';
	comp['{'] = '}';
	comp['<'] = '>';
	comp[')'] = '(';
	comp[']'] = '[';
	comp['}'] = '{';
	comp['>'] = '<';

	type['('] = true;
	type['['] = true;
	type['{'] = true;
	type['<'] = true;
	type[')'] = false;
	type[']'] = false;
	type['}'] = false;
	type['>'] = false;

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}