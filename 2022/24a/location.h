#ifndef LOCATION_H
#define LOCATION_H

#define COUT cout << __FUNCTION__ << ": "

#include <map>
#include <vector>

#include "directions.h"

class Location {
public:
	explicit Location();
	explicit Location(const char data);
	char toChar() const;
	bool isBlizzardDirection(const Direction& direction) const;
	std::vector<Direction> getBlizzardDirections() const;

	void setBlizzardDirection(const Direction direction);
	void clearBlizzardDirection(const Direction direction);

	void setExpedition(const bool hasExpedition);
	bool isEmpty() const;

	bool nblizzard = false, eblizzard = false, sblizzard = false, wblizzard = false, hasExpedition = false, isWall = false, isExit = false;
};
#endif // LOCATION_H
