#include "location.h"

#include <iostream>
#include <cassert>

using namespace std;

Location::Location() : ch('*') {}

Location::Location(const char data) {
	ch = data;
	switch (data) {
	case '^':
	{
		nblizzard = true;
		break;
	}
	case '>': {
		eblizzard = true;
		break;
	}
	case 'v': {
		sblizzard = true;
		break;
	}
	case '<':
	{
		wblizzard = true;
		break;
	}
	case 'E': {
		setExpedition(true);
		break;
	}
	case '#':{
		isWall = true;
		break;
	}
	case '.': {
		break;
	}
	default: {
		cout << "ERROR!! " << data << endl;
		assert (0);
		exit(1);
	}
	}
}

char Location::toChar() const {
	char numBlizzards = nblizzard ? 1 : 0;
	numBlizzards += eblizzard ? 1 : 0;
	numBlizzards += sblizzard ? 1 : 0;
	numBlizzards += wblizzard ? 1 : 0;
	if (numBlizzards == 0) {
		return (hasExpedition ? 'E' : isWall ? '#' : '.');
	}
	assert (hasExpedition == false);
	if (numBlizzards == 1) {
		char retval = (nblizzard ? '^' : eblizzard ? '>' : sblizzard ? 'v' : wblizzard ? '<' : '!');
		assert (retval != '!');
		return retval;
	}
	if (numBlizzards > 1) {
		return numBlizzards + '0';
	}
	assert(0);
	return '!';
}

bool Location::isBlizzardDirection(const Direction& direction) const {
	switch (direction) {
	case North: return nblizzard; break;
	case East: return eblizzard; break;
	case South: return sblizzard; break;
	case West: return wblizzard; break;
	}
	assert(0);
}

void Location::setBlizzardDirection(const Direction direction) {
	switch (direction) {
	case North: nblizzard = true; break;
	case East: eblizzard = true; break;
	case South: sblizzard = true; break;
	case West: wblizzard = true; break;
	default: assert (0);
	}

}

void Location::clearBlizzardDirection(const Direction direction) {
	switch (direction) {
	case North: nblizzard = false; break;
	case East: eblizzard = false; break;
	case South: sblizzard = false; break;
	case West: wblizzard = false; break;
	default: assert (0);
	}
}

std::vector<Direction> Location::getBlizzardDirections() const {
	vector<Direction> directions;
	if (nblizzard) {
		directions.push_back(North);
	}
	if (eblizzard) {
		directions.push_back(East);
	}
	if (sblizzard) {
		directions.push_back(South);
	}
	if (wblizzard) {
		directions.push_back(West);
	}
	return (directions);
}

void Location::setExpedition(const bool newval) {
	COUT << newval << endl;
	hasExpedition = newval;
}
