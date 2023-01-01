#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include "xy.h"

template <typename T>
class Grid {
public:

	explicit Grid(const char* filename) :
		minX(INT_MAX),
		minY(INT_MAX),
		maxX(INT_MIN),
		maxY(INT_MIN)
	{
	}
	explicit Grid() :
		minX(INT_MAX),
		minY(INT_MAX),
		maxX(INT_MIN),
		maxY(INT_MIN)
	{
	}

	const T& getElement(const xy& pos, bool& success) const {
		success = true;
		auto itx = _grid.find(pos.x);
		if (itx == _grid.end()) {
			//COUT << "can't find x " << pos.x << endl;
			success = false;
		}
		auto ity = itx->second.find(pos.y);
		if (ity == itx->second.end()) {
			//COUT << "can't find y " << pos.y << endl;
			success = false;
		}
		return ity->second;
	}

	T& getWritableElement(const xy& pos, bool& success) {
		success = true;
		auto itx = _grid.find(pos.x);
		if (itx == _grid.end()) {
			success = false;
		}
		auto ity = itx->second.find(pos.y);
		if (ity == itx->second.end()) {
			success = false;
		}
		return ity->second;
	}

	void write(const int x, const int y, const T location) {
		//COUT << "[" << x << "," << y << "]" << location.ch << " ";
		if (x < minX) {
			minX = x;
		}
		if (x > maxX) {
			maxX = x;
		}
		if (y < minY) {
			minY = y;
		}
		if (y > maxY) {
			maxY = x;
		}
		_grid[x][y] = location;
	}


	std::map<int, std::map<int, T> > _grid;
	int minX, minY, maxX, maxY;
};

#endif // GRID_H
