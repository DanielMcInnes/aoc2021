#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <string>
#include <cassert>

typedef enum {
	North,
	South,
	West,
	East
} Direction;

std::string toString(const Direction dir);
Direction opposite(const Direction dir);

#endif // DIRECTIONS_H
