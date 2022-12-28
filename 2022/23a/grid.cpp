#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

Grid::Grid(const char* filename) :
	minElfX(0),
	minElfY(0),
	maxElfX(0),
	maxElfY(0),
	elfCount(0)
{
	ifstream inputFile(filename);

	if (inputFile) {
		string line;
		int y  = 0;
		int x = 0;
		while (getline(inputFile, line))
		{
			cout << "line: " << line << endl;
			for (auto& ch : line) {
				if (ch == '#') {
					elfCount++;
				}
				write(x, y, Location(ch));
				//cout << "[" << x << "," << y << "] = " << ch;
				x++;
			}
			cout << endl;
			x = 0;
			y++;
		}
	}
	print();
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

void Grid::write(const int x, const int y, const Location& location) {
	_grid[x][y] = location;
}

void Grid::process() {
	cout << "grid size: " << _grid.size() << endl;
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			char ch = yline.second.ch;
			//cout << "[" << loc.x << "," << loc.y << "]" << ch << " ";
			if (isElf(loc)) {
				cout << "found an elf at " << loc.x << loc.y << " adjacent ? " << (isElfAdjacent(loc.x, loc.y) ? "yes" : "no") <<  endl;
				proposeMove(loc);
			}
		}
		cout << endl;
	}
	moveElves();
	changeDirections();
}

void Grid::moveElves() {
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy elfDestination(xline.first, yline.first);
			if (yline.second.elvesMovingFrom.size() > 0) {
				cout << "moveElves: [" << elfDestination.x << "," << elfDestination.y << "].proposedMoves: ";
				for (auto move : yline.second.elvesMovingFrom) {
					cout << "[" << move.x << "," << move.y << "]";
				}
				cout << endl;
				if (yline.second.elvesMovingFrom.size() > 1) {
					cout << "clearing proposed moves to " << elfDestination.x << "," << elfDestination.y << endl;
					yline.second.elvesMovingFrom.clear();
					break;
				}
				for (auto originalElfLocation : yline.second.elvesMovingFrom) {
					moveElf(originalElfLocation, elfDestination);
				}
			}
		}
	}
	print();
}

void Grid::moveElf(const xy& from, const xy& to) {
	cout << "elf moved from [" << from.x << "," << from.y << "]" << " to: [" << to.x << "," << to.y << "]" << endl;
	_grid[from.x][from.y].ch = '.';
	write(to.x, to.y, Location('#'));
}

void Grid::proposeMove(const xy& loc) {
	if (isElfAdjacent(loc.x, loc.y)) {
		for (Direction& dir : _directions) {
			if (elfCanMove(loc, dir)) {
				xy newloc(loc.relativeLocation(dir));
				cout << "elf at " << loc.x << " " << loc.y << " can move " << str(dir) << " to: " << newloc.x << newloc.y << endl;
				_grid[newloc.x][newloc.y].elvesMovingFrom.push_back(loc);
				break;
			}
		}
	} else {
		cout << "no elf adjacent to " << loc.x << " " << loc.y << endl;
	}
}

void Grid::getBoundingRectangle() {
	minElfX = 1000000;
	minElfY = 1000000;
	maxElfX = -1000000;
	maxElfY = -1000000;
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			if (isElf(loc)) {
				if (loc.x < minElfX) {
					minElfX = loc.x;
				}
				if (loc.y < minElfY) {
					minElfY = loc.y;
				}
				if (loc.x > maxElfX) {
					maxElfX = loc.x;
				}
				if (loc.y > maxElfY) {
					maxElfY = loc.y;
				}
			}
		}
	}
}

void Grid::print() {
	getBoundingRectangle();
	int emptyTiles = 0;
	for (int y = minElfY; y <= maxElfY; ++y) {
		for (int x = minElfX; x <= maxElfX; ++x) {
			cout << _grid[x][y].ch;
			if (_grid[x][y].ch == '.') {
				emptyTiles++;
			}
		}
		cout << endl;
	}
	int area = (maxElfX-minElfX) * (maxElfY - minElfY);
	cout << "minx: " << minElfX << " maxx: " << maxElfX << " miny: " << minElfY << " maxy: " << maxElfY << " area: " << area << endl;
	cout << "elves: " << elfCount << endl;
	cout << "empty tiles: " << emptyTiles << endl;
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
	bool retval = (strcmp(&ity->second.ch, ".") == 0);
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

	return (strcmp(&ity->second.ch, "#") == 0);
}

bool Grid::isElfAdjacent(const int x, const int y) const {
	return (isElf(x-1, y-1) || isElf(x, y-1) || isElf(x+1, y-1)	|| \
			isElf(x-1, y)					 || isElf(x+1, y)	|| \
			isElf(x-1, y+1) || isElf(x, y+1) || isElf(x+1, y+1)
			);
}

void Grid::changeDirections() {
	cout << "changing directions from " << str(_directions[0]) << " to: ";
	_directions.push_back(_directions[0]);
	_directions.erase(_directions.begin());
	cout << str(_directions[0]) << endl;
}
