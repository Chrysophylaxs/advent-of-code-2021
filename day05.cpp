#include <iostream>
#include <fstream>

enum Direction {
	Horizontal, Vertical, Diagonal, AntiDiagonal
};

struct Point {
	int x, y;

	bool operator!=(const Point& p) const { return p.x != x || p.y != y; }
	template<Direction d> Point next() const;
};

struct Line {
	Point p1, p2;

	template<Direction d> bool is() const;
	template<Direction d> Line start_end() const;
};

template<> Point Point::next<Horizontal>() const { return {x + 1, y}; }
template<> Point Point::next<Vertical>() const { return {x, y + 1}; }
template<> Point Point::next<Diagonal>() const { return {x + 1, y + 1}; }
template<> Point Point::next<AntiDiagonal>() const { return {x - 1, y + 1}; }

template<> bool Line::is<Horizontal>() const { return p1.y == p2.y; }
template<> bool Line::is<Vertical>() const { return p1.x == p2.x; }
template<> bool Line::is<Diagonal>() const { return p1.x - p2.x == p1.y - p2.y; }
template<> bool Line::is<AntiDiagonal>() const { return p1.x - p2.x == p2.y - p1.y; }

template<Direction d> Line Line::start_end() const {
	if (p1.y < p2.y || (p1.x < p2.x && p1.y == p2.y))
		return {p1, p2.next<d>()};
	else
		return {p2, p1.next<d>()};
}

std::istream& operator>>(std::istream& is, Point& p) { char comma; return is >> p.x >> comma >> p.y; }
std::istream& operator>>(std::istream& is, Line& l) { std::string arrow; return is >> l.p1 >> arrow >> l.p2; }

std::ostream& operator<<(std::ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }
std::ostream& operator<<(std::ostream& os, const Line& l) {	return os << l.p1 << " -> " << l.p2; }

//    Boilerplate      ^
// -------------------------------------------------------------------------------------------------------------------
//    Implementation   v

class OceanFloor {
public:
	void add(const Line& line) {
		if (line.is<Vertical>())
			add<Vertical>(line);
		
		else if (line.is<Horizontal>())
			add<Horizontal>(line);
		
		else if (line.is<Diagonal>())
			add<Diagonal>(line);

		else if (line.is<AntiDiagonal>())
			add<AntiDiagonal>(line);
	}

	int num_intersections() const {
		int total = 0;

		for (int i = 0; i < 1000; i++)
			for (int j = 0; j < 1000; j++)
				if (ocean_floor[i][j] > 1)
					total++;

		return total;
	}

private:
	void add(const Point& p) { ocean_floor[p.x][p.y]++; }

	template<Direction d>
	void add(const Line& line) {
		auto [start, end] = line.start_end<d>();
		for (Point curr = start; curr != end; curr = curr.next<d>())
			add(curr);
	}

	int ocean_floor[1000][1000] = {0};
};

Line lines[500];

int part1() {
	OceanFloor ocean;
	for (Line& line : lines)
		if (line.is<Horizontal>() || line.is<Vertical>())
			ocean.add(line);
	return ocean.num_intersections();
}

int part2() {
	OceanFloor ocean;
	for (Line& line : lines)
		ocean.add(line);
	return ocean.num_intersections();
}

int main() {
	std::ifstream input("in5.txt");

	for (Line& line : lines)
		input >> line;

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}
