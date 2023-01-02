#ifndef GRID24B_H
#define GRID24B_H

#include "grid.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

#include "blizzard.h"

template <typename KeyX, typename KeyY, typename Value>
class Grid24b : public Grid<KeyX, KeyY, Value>
{
public:
	explicit Grid24b(const char* filename) : Grid<KeyX, KeyY, Value>(filename)
	{
		std::ifstream inputFile(filename);
		bool foundexit = false;
		bool foundentrance = false;

		if (inputFile) {
			std::string line;
			KeyY y  = 0;
			KeyX x = 0;
			while (getline(inputFile, line))
			{
				std::cout << "line: " << line << std::endl;
				for (auto& ch : line) {
					this->write(x, y, Value(ch));
					x++;
				}
				x = 0;
				y++;
			}

			// find the entrance and exit
			for (auto& xline : this->_grid) {
				for (auto& yline : xline.second) {
					auto& position = yline.second;
					if (position.hasExpedition == true) {
						assert (foundentrance == false);
						foundentrance = true;
						position.isEntrance = true;
					}
					xy loc(xline.first, yline.first);
					if (loc.y == this->maxY && !position.isWall ) {
						position.isExit = true;
						_exit = loc;
						std::cout << "FOUND EXIT AT " << loc.x << loc.y << std::endl;
						assert(foundexit == false);
						foundexit = true;
					}
				}
			}
			std::cout << std::endl;
			inputFile.close();
		}
		assert(foundexit);

		print();

	}


	bool isEmpty(const xy& pos) const {
		bool result;
		const Value& loc(this->getElement(pos, result));
		if (result) {
			return (loc.isEmpty());
		}
		return false;
	}

	bool expeditionCanMove(const xy& loc, const Direction direction) const {
		xy nextPosition(loc.relativeLocation(direction));
		//cout << __FUNCTION__ << ": nextPosition: "<< nextPosition.x << " " << nextPosition.y << endl;
		bool result = false;
		const Value& nextLocation(this->getElement(nextPosition, result));
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
		if (nextLocation.hasExpedition) {
			//cout << __FUNCTION__ << ": ret false, already has expedition" << endl;
			return false;
		}
		assert(nextLocation.nblizzard || nextLocation.eblizzard || nextLocation.sblizzard || nextLocation.wblizzard);
		//cout << __FUNCTION__ << ": ret true, there is a blizzard moving out of the way" << endl;
		return true;
	}

	void print() const {
		for (KeyY y = this->minY; y <= this->maxY; ++y) {
			for (KeyX x = this->minX; x <= this->maxX; ++x) {
				char ch = this->_grid.at(x).at(y).toChar();
				//cout << "[" << x << "," << y << "]" << ch;
				std::cout << ch;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	bool isWall(const xy& loc) const {
		bool result;
		const Value& location(this->getElement(loc, result));
		if (result) {
			return location.isWall;
		}
		return false;
	}


	void process() {
		for (auto& xline : this->_grid) {
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

	void moveExpeditions() {
		bool result = false;
		for (const auto& pos  : pendingExpeditionMoves) {
			Value& loc(this->getWritableElement(pos, result));
			assert(result);
			loc.setExpedition(true);
			if (loc.isExit) {
				std::cout << "!!!!!!!! FOUND IT !!!!!!!!!!!" << std::endl;
				_foundExit = true;
			}
			if (loc.isEntrance) {
				_foundEntrance = true;
			}
		}
		pendingExpeditionMoves.clear();
	}

	void spawnNeighbouringExpeditions(const xy& position) {
		// cout << __FUNCTION__ << ": "<< position.x << " " << position.y << endl;
		for (const Direction& dir : _directions) {
			xy nextPosition(position.relativeLocation(dir));
			if (expeditionCanMove(position, dir)) {
				//COUT << "setting expedition true at " << nextPosition.x << "," << nextPosition.y << endl;
				pendingExpeditionMoves.push_back(nextPosition);
			}
		}
	}
	void clearExpeditions(const bool clearEntrance = false, const bool clearExit = false) {
		for (KeyY y = this->minY; y <= this->maxY; ++y) {
			for (KeyX x = this->minX; x <= this->maxX; ++x) {
				auto& loc = this->_grid.at(x).at(y);
				if ((!loc.isEntrance || clearEntrance) && (!loc.isExit || clearExit)) {
					loc.setExpedition(false);
				}
			}
		}
	}

	void moveBlizzards() {
		for (auto& xline : this->_grid) {
			for (auto& yline : xline.second) {
				xy position(xline.first, yline.first);
				Value& loc = yline.second;
				for (const Direction& dir : loc.getBlizzardDirections()) {
					moveBlizzard(position, loc, dir);
				}
			}
		}
		for(const auto& blizzard : pendingBlizzardMoves) {
			bool result = false;

			Value& loc(this->getWritableElement(blizzard._newpos, result));
			assert(result);
			loc.setBlizzardDirection(blizzard._direction);
			loc.setExpedition(false);
		}
		pendingBlizzardMoves.clear();
	}
	void moveBlizzard(const xy& from, Value& oldPosition, const Direction direction) {
		//COUT << from.x << "," << from.y << " " << toString(direction) << endl;
		bool result;
		xy newPosition(from.relativeLocation(direction));
		Value& newLocation(this->getWritableElement(newPosition, result));
		if (result) {
			if (newLocation.isWall) {
				switch (direction) {
				case North: {
					newPosition.y = this->maxY - 1;
					break;
				}
				case East: {
					newPosition.x = this->minX + 1;
					break;
				}
				case South: {
					newPosition.y = this->minY + 1;
					break;
				}
				case West: {
					newPosition.x = this->maxX - 1;
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
		Blizzard blizzard(from, newPosition, direction);
		pendingBlizzardMoves.push_back(blizzard);
		oldPosition.clearBlizzardDirection(direction);
	}

	std::vector<xy> pendingExpeditionMoves;
	std::vector<Blizzard> pendingBlizzardMoves;
	xy _exit;
	const std::vector<Direction> _directions{North, East, South, West};
	bool _foundExit = false;
	bool _foundEntrance = false;
};

#endif // GRID24B_H
