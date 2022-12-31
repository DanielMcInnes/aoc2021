#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include <cassert>
#include <iostream>
#include "location.h"
#include "blizzard.h"
#include "xy.h"

class Grid {
public:

	explicit Grid(const char* filename);
	void process();

	bool expeditionCanMove(const xy& loc, const Direction direction) const;
	xy relativeLocation(const xy& loc, const Direction direction) const;
	bool isEmpty(const xy& pos) const;
	bool isWall(const xy& loc) const;
	bool isOncomingBlizzard(const xy& myPosition, const Direction myDirection) const;
	const Location& getValidLocation(const xy& pos, bool& success) const;
	Location& getWritableValidLocation(const xy& pos, bool& success);
	void print() const;

	void spawnNeighbouringExpeditions(const xy& loc);
	void moveBlizzards();
	void moveBlizzard(const xy& from, Location& location, const Direction direction);
	void write(const int x, const int y, const Location location);
	void getBoundingRectangle();
	void moveExpeditions();
	void clearExpeditions(const bool clearEntrance = false, const bool clearExit = false);

	std::map<int, std::map<int, Location> > _grid;
	const std::vector<Direction> _directions{North, East, South, West};
	int minX, minY, maxX, maxY;
	std::vector<xy> pendingExpeditionMoves;
	std::vector<Blizzard> pendingBlizzardMoves;
	xy _exit;
	bool _foundExit = false;
	bool _foundEntrance = false;
};

#endif // GRID_H
