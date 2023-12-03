#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include "xy.h"

template <typename KeyX, typename KeyY, typename Value>
class map2d {
public:

	explicit map2d(const char* filename) :
		minX(INT_MAX),
		minY(INT_MAX),
		maxX(INT_MIN),
		maxY(INT_MIN)
	{
	}
	explicit map2d() :
		minX(INT_MAX),
		minY(INT_MAX),
		maxX(INT_MIN),
		maxY(INT_MIN)
	{
	}

	const Value& getElement(const xy& pos, bool& success) const {
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

	Value& getWritableElement(const xy& pos, bool& success) {
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

	void write(const KeyX x, const KeyY y, const Value location) {
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


	std::map<KeyX, std::map<KeyY, Value> > _grid;
	KeyX minX, maxX;
	KeyY minY, maxY;
};

#endif // GRID_H
