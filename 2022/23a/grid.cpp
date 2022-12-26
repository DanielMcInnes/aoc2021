#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

Grid::Grid(const char* filename) {
	ifstream inputFile(filename);

	if (inputFile) {
		string line;
		int y  = 0;
		int x = 0;
		while (getline(inputFile, line))
		{
			cout << "line: " << line << endl;
			for (auto& ch : line) {
				_grid[x][y] = ch;
				cout << "[" << x << "," << y << "] = " << ch;
				x++;
			}
			cout << endl;
			x = 0;
			y++;
		}
	}
}

string str(const Direction direction) {
	switch (direction) {
	case North: return "north";
	case South: return "south";
	case East: return "east";
	case West: return "west";
	}
	assert (0);
	return "";
}

void Grid::process() {
	cout << "grid size: " << _grid.size() << endl;
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			char ch = yline.second;
			//cout << "[" << loc.x << "," << loc.y << "]" << ch << " ";
			if (isElf(loc)) {
				cout << "found an elf at " << loc.x << loc.y << " adjacent ? " << (isElfAdjacent(loc.x, loc.y) ? "yes" : "no") <<  endl;
				proposeMove(loc);
			}
		}
		cout << endl;
	}
}

void Grid::proposeMove(const xy& loc) {
	if (isElfAdjacent(loc.x, loc.y)) {
		for (Direction& dir : _directions) {
			if (elfCanMove(loc, dir)) {
				cout << "elf at " << loc.x << " " << loc.y << " can move " << str(dir) << endl;
			}
		}
	} else {
		cout << "no elf adjacent to " << loc.x << " " << loc.y << endl;
	}
}

bool Grid::elfCanMove(const xy& loc, const Direction direction) const {
	//cout << "elfCanMove(" << loc.x << loc.y << ")" << str(direction) << endl;
	switch (direction) {
	case North: return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x, loc.y-1) && isEmpty(loc.x+1, loc.y-1));
	case South: return (isEmpty(loc.x-1, loc.y+1) && isEmpty(loc.x, loc.y+1) && isEmpty(loc.x+1, loc.y+1));
	case East:  {
		return (isEmpty(loc.x+1, loc.y-1) && isEmpty(loc.x+1, loc.y) && isEmpty(loc.x+1, loc.y+1));
	}
	case West:  return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x-1, loc.y) && isEmpty(loc.x-1, loc.y+1));
	}
	assert(0);
}

bool Grid::isEmpty(const int x, const int y) const{
	//cout << "isEmpty: " << x << " " << y;
	auto itx = _grid.find(x);
	if (itx == _grid.end()) {
		//cout << " grid x end: true" << endl;
		return true;
	}
	auto ity = itx->second.find(y);
	if (ity == itx->second.end()) {
		return true;
		//cout << " grid y end: true" << endl;
	}
	bool retval = (strcmp(&ity->second, ".") == 0);
	//cout << (retval ? "true" : "false") << endl;
	return (retval);
}

bool Grid::isElf(const xy& loc) const {
	return (isElf(loc.x, loc.y));
}

bool Grid::isElf(const int x, const int y) const {
	auto itx = _grid.find(x);
	if (itx == _grid.end()) {
		return false;
	}
	auto ity = itx->second.find(y);
	if (ity == itx->second.end()) {
		return false;
	}
	//cout << "isElf:" << x << "," << y <<"):" << ity->second << endl;

	return (strcmp(&ity->second, "#") == 0);
}

bool Grid::isElfAdjacent(const int x, const int y) const {
	return (isElf(x-1, y-1) || isElf(x, y-1) || isElf(x+1, y-1)	|| \
			isElf(x-1, y)					 || isElf(x+1, y)	|| \
			isElf(x-1, y+1) || isElf(x, y+1) || isElf(x+1, y+1)
			);
}
