#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

//#include "blizzard.h"

using namespace std;

string toString(const Direction dir) {
	switch (dir) {
	case North: return "north"; break;
	case East: return "east"; break;
	case South: return "south"; break;
	case West: return "west"; break;
	}
	assert(0);
}

Grid::Grid(const char* filename) :
	minX(INT_MAX),
	minY(INT_MAX),
	maxX(INT_MIN),
	maxY(INT_MIN)
{
	ifstream inputFile(filename);
	bool foundexit = false;
	bool foundentrance = false;

	if (inputFile) {
		string line;
		int y  = 0;
		int x = 0;
		while (getline(inputFile, line))
		{
			cout << "line: " << line << endl;
			for (auto& ch : line) {
				write(x, y, Location(ch));
				x++;
			}
			x = 0;
			y++;
		}

		// find the entrance and exit
		for (auto& xline : _grid) {
			for (auto& yline : xline.second) {
				auto& position = yline.second;
				if (position.hasExpedition == true) {
					assert (foundentrance == false);
					foundentrance = true;
					position.isEntrance = true;
				}
				xy loc(xline.first, yline.first);
				if (loc.y == maxY && !position.isWall ) {
					position.isExit = true;
					_exit = loc;
					cout << "FOUND EXIT AT " << loc.x << loc.y << endl;
					assert(foundexit == false);
					foundexit = true;
				}
			}
		}
		cout << endl;
		inputFile.close();
	}
	assert(foundexit);

	print();
}

void Grid::write(const int x, const int y, const Location location) {
	//COUT << "[" << x << "," << y << "]" << location.ch << " ";
	if (x < minX) {
		minX = x;
	}
	if (x > maxX) {
		maxX = x;
	}
	if (y < minY) {
		minY = y;
	}
	if (y > maxY) {
		maxY = x;
	}
	_grid[x][y] = location;
}

void Grid::process() {
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			const auto position = yline.second;
			xy loc(xline.first, yline.first);
			if (position.hasExpedition) {
				spawnNeighbouringExpeditions(loc);
			}
		}
	}
	moveExpeditions();
	moveBlizzards();
}

void Grid::moveExpeditions() {
	bool result = false;
	for (const auto& pos  : pendingExpeditionMoves) {
		Location& loc(getWritableValidLocation(pos, result));
		assert(result);
		loc.setExpedition(true);
		if (loc.isExit) {
			cout << "!!!!!!!! FOUND IT !!!!!!!!!!!" << endl;
			_foundExit = true;
		}
	}
	pendingExpeditionMoves.clear();
}

void Grid::spawnNeighbouringExpeditions(const xy& position) {
	// cout << __FUNCTION__ << ": "<< position.x << " " << position.y << endl;
	for (const Direction& dir : _directions) {
		xy nextPosition(position.relativeLocation(dir));
		if (expeditionCanMove(position, dir)) {
			//COUT << "setting expedition true at " << nextPosition.x << "," << nextPosition.y << endl;
			pendingExpeditionMoves.push_back(nextPosition);
		}
	}
}

void Grid::moveBlizzards() {
	for (auto& xline : _grid) {
		for (auto& yline : xline.second) {
			xy position(xline.first, yline.first);
			Location& loc = yline.second;
			for (const Direction& dir : loc.getBlizzardDirections()) {
				moveBlizzard(position, loc, dir);
			}
		}
	}
	for(const auto& blizzard : pendingBlizzardMoves) {
		bool result = false;

		Location& loc(getWritableValidLocation(blizzard._newpos, result));
		assert(result);
		loc.setBlizzardDirection(blizzard._direction);
		loc.setExpedition(false);
	}
	pendingBlizzardMoves.clear();
}

void Grid::moveBlizzard(const xy& oldPosition, Location& location, const Direction direction ) {
	//COUT << from.x << "," << from.y << " " << toString(direction) << endl;
	bool result;
	xy newPosition(oldPosition.relativeLocation(direction));
	Location& newLocation(getWritableValidLocation(newPosition, result));
	if (result) {
		if (newLocation.isWall) {
			switch (direction) {
			case North: {
				newPosition.y = maxY - 1;
				break;
			}
			case East: {
				newPosition.x = minX + 1;
				break;
			}
			case South: {
				newPosition.y = minY + 1;
				break;
			}
			case West: {
				newPosition.x = maxX - 1;
				break;
			}
			default: {
				assert(0);
			}
			}
		}
	}
	else {
		assert(0);
	}
	Blizzard blizzard(oldPosition, newPosition, direction);
	pendingBlizzardMoves.push_back(blizzard);
	location.clearBlizzardDirection(direction);
}

void Grid::getBoundingRectangle() {
}

void Grid::print() const {
	int x = 0;
	int y = 0;
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			char ch = _grid.at(x).at(y).toChar();
			//cout << "[" << x << "," << y << "]" << ch;
			cout << ch;
		}
		cout << endl;
	}
	cout << endl;
}

bool Grid::expeditionCanMove(const xy& position, const Direction direction) const {
	xy nextPosition(position.relativeLocation(direction));
	//cout << __FUNCTION__ << ": nextPosition: "<< nextPosition.x << " " << nextPosition.y << endl;
	bool result = false;
	const Location& nextLocation(getValidLocation(nextPosition, result));
	if (!result) {
		//cout << __FUNCTION__ << ": ret false, can't move outside of the grid" << endl;
		return false; // can't move outside of the grid
	}
	if (nextLocation.isWall) {
		//cout << __FUNCTION__ << ": ret false, can't move through walls" << endl;
		return false;
	}
	if (isEmpty(nextPosition)) {
		//cout << __FUNCTION__ << ": ret true, next pos is empty" << endl;
		return true;
	}
	if (isWall(nextPosition)) {
		//cout << __FUNCTION__ << ": ret false, wall" << endl;
		return false;
	}
	/*
	if (isOncomingBlizzard(position, direction)) {
		//cout << __FUNCTION__ << ": ret false, oncoming blizzard" << endl;
		return false;
	}
	*/
	if (nextLocation.hasExpedition) {
		//cout << __FUNCTION__ << ": ret false, already has expedition" << endl;
		return false;
	}
	assert(nextLocation.nblizzard || nextLocation.eblizzard || nextLocation.sblizzard || nextLocation.wblizzard);
	//cout << __FUNCTION__ << ": ret true, there is a blizzard moving out of the way" << endl;
	return true;
}

Direction opposite(const Direction dir) {
	switch (dir) {
	case North: return South; break;
	case East: return West; break;
	case South: return North; break;
	case West: return East; break;
	}
	assert (0);
}

bool Grid::isOncomingBlizzard(const xy& myPosition, const Direction myDirection) const {
	xy nextPosition(myPosition.relativeLocation(myDirection));
	bool result;
	const Location& nextLocation(getValidLocation(nextPosition, result));
	if (result) {
		if (nextLocation.isBlizzardDirection(opposite(myDirection))) {
			return true;
		}
	}
	return false;
}

const Location& Grid::getValidLocation(const xy& pos, bool& success) const {
	success = true;
	auto itx = _grid.find(pos.x);
	if (itx == _grid.end()) {
		//COUT << "can't find x " << pos.x << endl;
		success = false;
	}
	auto ity = itx->second.find(pos.y);
	if (ity == itx->second.end()) {
		//COUT << "can't find y " << pos.y << endl;
		success = false;
	}
	return ity->second;
}

Location& Grid::getWritableValidLocation(const xy& pos, bool& success) {
	success = true;
	auto itx = _grid.find(pos.x);
	if (itx == _grid.end()) {
		success = false;
	}
	auto ity = itx->second.find(pos.y);
	if (ity == itx->second.end()) {
		success = false;
	}
	return ity->second;
}

bool Grid::isEmpty(const xy& pos) const {
	bool result;
	const Location& loc(getValidLocation(pos, result));
	if (result) {
		return (loc.isEmpty());
	}
	return false;
}

bool Grid::isWall(const xy& pos) const {
	bool result;
	const Location& location(getValidLocation(pos, result));
	if (result) {
		return location.isWall;
	}
	return false;
}

void Grid::clearExpeditions(const bool clearEntrance, const bool clearExit) {
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			auto loc = _grid.at(x).at(y);
			if (loc.isEntrance && clearEntrance) {
				loc.setExpedition(false);
			}
			else if (loc.isExit && clearExit) {
				loc.setExpedition(false);
			}
			else {
				loc.setExpedition(false);
			}
		}
	}
}
