#include "blizzard.h"

Blizzard::Blizzard()
{

}
Blizzard::Blizzard(const xy& pos, const Direction dir) :
	_pos(pos),
	_direction(dir) {
}
