#include <iostream>
#include <vector>

enum CaveType { VisitOnce, VisitMultiple };

struct Cave {
	Cave() {}
	Cave(std::vector<Cave*> c, CaveType t=VisitOnce) : neighbors(c), type(t) {}
	
	std::vector<Cave*> neighbors = {};
	CaveType type;
	bool visited = false;
};

Cave start, dr, of, KT, yj, sk, gb, IJ, km, PZ, VT, end;

int dfs(Cave* curr, bool twice=false);

int search(Cave* curr, bool twice=false) {
	int tot = 0;
	for (Cave* c : curr->neighbors)
		tot += dfs(c, twice);

	return tot;
}

int dfs(Cave* curr, bool twice) {
	if (curr->type == VisitOnce && curr->visited)
		return (!twice || curr == &start) ? 0 : search(curr);

	if (curr == &end)
		return 1;

	curr->visited = true;
	int tot = search(curr, twice);
	curr->visited = false;

	return tot;
}

int part1() { return dfs(&start); }

int part2() { return dfs(&start, true); }

int main() {
	start = Cave({&of, &KT, &gb});
	dr    = Cave({&of, &IJ, &yj, &PZ, &sk, &VT});
	of    = Cave({&dr, &start, &IJ, &VT, &KT, &gb});
	KT    = Cave({&start, &end, &gb, &of, &yj}, VisitMultiple);
	yj    = Cave({&sk, &IJ, &KT, &dr});
	sk    = Cave({&dr, &yj, &VT, &end});
	gb    = Cave({&start, &VT, &of, &KT});
	IJ    = Cave({&end, &of, &dr, &yj}, VisitMultiple);
	km    = Cave({&VT});
	PZ    = Cave({&dr}, VisitMultiple);
	VT    = Cave({&sk, &km, &gb, &dr, &of}, VisitMultiple);
	end   = Cave({&IJ, &sk, &KT});

	std::cout << "Part1: " << part1() << std::endl;
	std::cout << "Part2: " << part2() << std::endl;

	return 0;
}