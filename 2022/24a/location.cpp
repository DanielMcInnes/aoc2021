#include "location.h"

#include <iostream>
#include <cassert>

using namespace std;
Location::Location(const char data) {
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
		expedition = true;
		break;
	}
	case '#':{
		wall = true;
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
		return (expedition ? 'E' : wall ? '#' : '.');
	}
	assert (expedition == false);
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
