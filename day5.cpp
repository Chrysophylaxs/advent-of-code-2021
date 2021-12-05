#include <iostream>
#include <fstream>

enum Direction {
	Horizontal, Vertical, Diagonal, AntiDiagonal
};

struct Point {
	int x, y;

	bool operator!=(const Point& p) { return p.x != x || p.y != y; }
	template<Direction d> Point& next();
};

struct Line {
	Point p1, p2;

	template<Direction d> bool is() const;
	template<Direction d> Line start_end();
};

template<> Point& Point::next<Horizontal>() { x++; return *this; }
template<> Point& Point::next<Vertical>() { y++; return *this; }
template<> Point& Point::next<Diagonal>() { x++; y++; return *this; }
template<> Point& Point::next<AntiDiagonal>() { x--; y++; return *this; }

template<> bool Line::is<Horizontal>() const { return p1.y == p2.y; }
template<> bool Line::is<Vertical>() const { return p1.x == p2.x; }
template<> bool Line::is<Diagonal>() const { return p1.x - p2.x == p1.y - p2.y; }
template<> bool Line::is<AntiDiagonal>() const { return p1.x - p2.x == p2.y - p1.y; }

template<Direction d> Line Line::start_end() {
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
	void add(Point p) { ocean_floor[p.x][p.y]++; }

	template<Direction d>
	void add(Line l) {
		auto [start, end] = l.start_end<d>();
		for (Point p = start; p != end; p.next<d>())
			add(p);
	}

	int ocean_floor[1000][1000] = {0};
};

Line lines[500];

int part1() {
	OceanFloor ocean;
	for (int i = 0; i < 500; i++)
		if (lines[i].is<Horizontal>() || lines[i].is<Vertical>())
			ocean.add(lines[i]);
	return ocean.num_intersections();
}

int part2() {
	OceanFloor ocean;
	for (int i = 0; i < 500; i++)
		ocean.add(lines[i]);
	return ocean.num_intersections();
}

int main() {
	std::ifstream input("in5.txt");

	for (int i = 0; i < 500; i++)
		input >> lines[i];

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}