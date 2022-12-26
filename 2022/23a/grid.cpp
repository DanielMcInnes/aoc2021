#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

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
				_grid[y][x] = ch;
				x++;
			}
			x = 0;
			y++;
		}
	}
}

string str(const Direction direction) {
	switch (direction) {
	case North: return ("north");
	case South: return "south";
	case East: return "east";
	case West: return "west";
	}
}

void Grid::process() {
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			int x = xline.first;
			int y = yline.first;
			char ch = yline.second;
			cout << "[" << loc.x << "," << loc.y << "]" << ch << " ";
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
		Direction dir = _directions.at(0);
	} else {
		cout << "no elf adjacent to " << loc.x << " " << loc.y << endl;
	}
}

bool Grid::elfCanMove(const xy& loc, const Direction direction) const {
	switch (direction) {
	case North: return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x, loc.y-1) && isEmpty(loc.x+1, loc.y-1));
	case South: return (isEmpty(loc.x-1, loc.y+1) && isEmpty(loc.x, loc.y+1) && isEmpty(loc.x+1, loc.y+1));
	case East:  return (isEmpty(loc.x+1, loc.y-1) && isEmpty(loc.x+1, loc.y) && isEmpty(loc.x+1, loc.y+1));
	case West:  return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x-1, loc.y) && isEmpty(loc.x-1, loc.y+1));
	}
	assert(0);
}

xy Grid::relativeLocation(const int x, const int y, const Direction direction) const {
	switch (direction) {
	case North: return (xy(x, y-1));
	case South: return (xy(x, y+1));
	case East: return (xy(x+1, y));
	case West: return (xy(x-1, y));
	}
}

bool Grid::isEmpty(const int x, const int y) const{
	auto itx = _grid.find(x);
	if (itx == _grid.end()) {
		return true;
	}
	auto ity = itx->second.find(y);
	if (ity == itx->second.end()) {
		return true;
	}
	return (strcmp(&ity->second, ".") == 0);
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
	cout << "isElf:" << x << "," << y <<"):" << ity->second << endl;

	return (strcmp(&ity->second, "#") == 0);
}

bool Grid::isElfAdjacent(const int x, const int y) const {
	return (isElf(x-1, y-1) || isElf(x, y-1) || isElf(x+1, y-1)	|| \
			isElf(x-1, y)					 || isElf(x+1, y)	|| \
			isElf(x-1, y+1) || isElf(x, y+1) || isElf(x+1, y+1)
			);
}
