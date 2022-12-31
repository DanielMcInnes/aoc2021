#ifndef BLIZZARD_H
#define BLIZZARD_H

#include "location.h"
#include "xy.h"

class Blizzard
{
public:
	Blizzard();
	Blizzard(const xy& oldpos, const xy& newpos, const Direction dir);
	Direction _direction;
	const xy _newpos;
	const xy _oldpos;
};

#endif // BLIZZARD_H
