#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

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
			for (auto& ch : line) {
				if (ch == '#') {
					elfCount++;
				}
				write(x, y, Location(ch));
				x++;
			}
			x = 0;
			y++;
		}
		inputFile.close();
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

void Grid::write(const int x, const int y, const Location& location) {
	assert(location.elvesMovingFrom.size() == 0);
	assert(_grid[x][y].ch == '.');
	_grid[x][y] = location;
}

bool Grid::process() {
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			//char ch = yline.second.ch;
			//cout << "[" << loc.x << "," << loc.y << "]" << ch << " ";
			if (yline.second.ch == '#') {
				proposeMove(loc);
			}
		}
	}
	bool elfMoved = moveElves();
	changeDirections();
	return elfMoved;
}

void Grid::proposeMove(const xy& loc) {
	if (isElfAdjacent(loc.x, loc.y)) {
		for (Direction& dir : _directions) {
			xy newloc(loc.relativeLocation(dir));
			if (elfCanMove(loc, dir)) {
				_grid[newloc.x][newloc.y].elvesMovingFrom.push_back(loc);
				break;
			}
		}
	}
}

bool Grid::moveElves() {
	bool elfMoved = false;
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy elfDestination(xline.first, yline.first);
			if (yline.second.elvesMovingFrom.size() > 0) {
				if (yline.second.elvesMovingFrom.size() > 1) {
					yline.second.elvesMovingFrom.clear();
				}
				assert(yline.second.elvesMovingFrom.size() <= 1);
				for (auto originalElfLocation : yline.second.elvesMovingFrom) {
					moveElf(originalElfLocation, elfDestination);
					elfMoved = true;
				}
				yline.second.elvesMovingFrom.clear();
			}
		}
	}
	return elfMoved;
}

void Grid::moveElf(const xy& from, const xy& to) {
	assert(_grid[from.x][from.y].ch = '#');
	_grid[from.x][from.y].ch = '.';
	_grid[from.x][from.y].elvesMovingFrom.clear();
	assert(_grid[to.x][to.y].ch == '.');
	write(to.x, to.y, Location('#'));
	_grid[to.x][to.y].elvesMovingFrom.clear();
	assert(_grid[to.x][to.y].elvesMovingFrom.size() == 0);
}

void Grid::getBoundingRectangle() {
	minElfX = INT_MAX;
	minElfY = INT_MAX;
	maxElfX = INT_MIN;
	maxElfY = INT_MIN;
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy loc(xline.first, yline.first);
			if (yline.second.ch == '#') {
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
			if (_grid[x][y].ch == '.') {
				emptyTiles++;
			}
		}
	}
	int area = (maxElfX-minElfX) * (maxElfY - minElfY);
	cout << "minx: " << minElfX << " maxx: " << maxElfX << " miny: " << minElfY << " maxy: " << maxElfY << " area: " << area << endl;
	//cout << "elves: " << elfCount << endl;
	cout << "empty tiles: " << emptyTiles << endl;
}

bool Grid::elfCanMove(const xy& loc, const Direction direction) {
	switch (direction) {
	case North: return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x, loc.y-1) && isEmpty(loc.x+1, loc.y-1));
	case South: return (isEmpty(loc.x-1, loc.y+1) && isEmpty(loc.x, loc.y+1) && isEmpty(loc.x+1, loc.y+1));
	case East:  return (isEmpty(loc.x+1, loc.y-1) && isEmpty(loc.x+1, loc.y) && isEmpty(loc.x+1, loc.y+1));
	case West:  return (isEmpty(loc.x-1, loc.y-1) && isEmpty(loc.x-1, loc.y) && isEmpty(loc.x-1, loc.y+1));
	}
	assert(0);
}

bool Grid::isEmpty(const int x, const int y) {
	bool retval = _grid[x][y].ch == '.';
	return (retval);
}

bool Grid::isElf(int x, int y) {
	return (_grid[x][y].ch == '#');
}

bool Grid::isElfAdjacent(const int x, const int y) {
	return (isElf(x-1, y-1) || isElf(x, y-1) || isElf(x+1, y-1)	|| \
			isElf(x-1, y)					 || isElf(x+1, y)	|| \
			isElf(x-1, y+1) || isElf(x, y+1) || isElf(x+1, y+1)
			);
}

void Grid::changeDirections() {
	_directions.push_back(_directions[0]);
	_directions.erase(_directions.begin());
}
