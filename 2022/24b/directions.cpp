#include "directions.h"

std::string toString(const Direction dir) {
	switch (dir) {
	case North: return "north"; break;
	case East: return "east"; break;
	case South: return "south"; break;
	case West: return "west"; break;
	}
	assert(0);
}

Direction opposite(const Direction dir) {
	switch (dir) {
	case North: return South; break;
	case East: return West; break;
	case South: return North; break;
	case West: return East; break;
	}
	assert (0);
}

