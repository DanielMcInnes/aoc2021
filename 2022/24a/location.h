#ifndef LOCATION_H
#define LOCATION_H

#include <map>

class Location {
public:
	explicit Location() {
	}

	explicit Location(const char data);
	char toChar() const;
	bool nblizzard = false, eblizzard = false, sblizzard = false, wblizzard = false, expedition = false, wall = false;
	char ch;
};
#endif // LOCATION_H
