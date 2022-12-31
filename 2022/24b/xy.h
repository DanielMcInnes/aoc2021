#ifndef XY_H
#define XY_H

#include <cassert>
#include "directions.h"

class xy
{
public:
	xy();
	xy(const int x, const int y) : x(x), y(y) {}
	int x;
	int y;
	xy relativeLocation(const Direction direction) const {
		switch (direction) {
		case North: return (xy(x, y-1));
		case South: return (xy(x, y+1));
		case East: return (xy(x+1, y));
		case West: return (xy(x-1, y));
		}
		assert(0);
		return xy(0,0);
	}
};

#endif // XY_H
