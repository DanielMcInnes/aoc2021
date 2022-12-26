#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include <cassert>

typedef enum {
	North,
	South,
	West,
	East
} Direction;

class xy {
public:
	xy(const int x, const int y) : x(x), y(y) {}
	int x;
	int y;
	xy relativeLocation(const Direction direction) const {
		switch (direction) {
		case North: return (xy(x, y-1));
		case South: return (xy(x, y+1));
		case East: return (xy(x+1, y));
		case West: return (xy(x-1, y));
		}
		assert(0);
		return xy(0,0);
	}
};

class Location {
public:
	explicit Location(const char data) : ch(data) {
	}
	char ch;
	std::vector< std::pair<int, int> > proposedMoves; // the 'from' coordinates of elves that propose to move here
};


class Grid {
public:

	explicit Grid(const char* filename);
	void process();

private:
	void proposeMove(const xy& loc);
	bool elfCanMove(const xy& loc, const Direction direction) const;
	xy relativeLocation(const xy& loc, const Direction direction) const;
	bool isEmpty(const int x, const int y) const;
	bool isElf(const xy& loc) const;
	bool isElf(const int x, const int y) const;
	bool isElfAdjacent(const int x, const int y) const;
	std::map<int, std::map<int, char> > _grid;
	std::vector<Direction> _directions{North, South, West, East};
};

#endif // GRID_H
