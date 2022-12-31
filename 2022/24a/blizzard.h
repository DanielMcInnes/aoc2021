#ifndef BLIZZARD_H
#define BLIZZARD_H

#include "location.h"
#include "xy.h"

class Blizzard
{
public:
	Blizzard();
	Blizzard(const xy& pos, const Direction dir);
	Direction _direction;
	xy _pos;
};

#endif // BLIZZARD_H
