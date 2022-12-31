#include "blizzard.h"

Blizzard::Blizzard()
{

}
Blizzard::Blizzard(const xy& oldpos, const xy& newpos, const Direction dir) :
	_oldpos(oldpos),
	_newpos(newpos),
	_direction(dir) {
}
