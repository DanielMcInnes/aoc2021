#ifndef MAP22A_H
#define MAP22A_H
#include "map2d.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <string>

#include "directions.h"
#include "xy.h"

using namespace std;

template <typename KeyX, typename KeyY, typename Value>
class map22a : public map2d<KeyX, KeyY, Value>
{
public:
	explicit map22a(const char* filename) : map2d<KeyX, KeyY, Value>(filename) {
		std::ifstream inputFile(filename);

		if (inputFile) {
			std::string line;
			KeyY y  = 0;
			KeyX x = 0;
			while (getline(inputFile, line))
			{
				std::cout << "line: " << line << " length: " << line.length() << std::endl;
				if (line.length() > 0) {
					for (auto& ch : line) {
						this->write(x, y, Value(ch));
						x++;
					}
					x = 0;
					y++;
				} else {
					getline(inputFile, path);
				}
			}
			this->print();
		}
		else {
			assert(0);
		}
		bool found = false;
		int x = 0;
		KeyY y = this->minY;
		while (true) {
			char ch = this->getElement(xy(x, y), found);
			if (ch == '.') {
				break;
			}
			x++;
		}
		cout << "found start at " << x << "," << y << endl;
		_pos.x = x;
		_pos.y = y;
	}

	void process() {
		while (path.length() > 0) {
			if (path.find_first_of(numbers) == 0) {
				move(findDistance());
			} else {
				turn();
				cout << "direction: " << toString(_dir) << endl;
			}
		}
	}

	void turn() {
		assert(path.find_first_of(letters) == 0);
		char dir = path.at(0);
		int d;
		switch (dir) {
		case 'L':
			d = (_dir + 3) % 4;
			break;
		case 'R':
			d = (_dir + 1) % 4;
			break;
		default:
			assert(0);
		}
		_dir = static_cast<Direction>(d);
		path.erase(0, 1);
	}

	int findDistance() {
		size_t endOfNumber = path.find_first_not_of(numbers);
		if (endOfNumber == string::npos) {
			assert(0);
		}

		int distance = stoi(path.substr(0, endOfNumber));
		path.erase(0, endOfNumber);
		cout << "distance: " << distance << " path: " << path << endl;
		return distance;
		move(distance);
	}

	void move(int distance) {
		bool result = false;
		while (distance > 0) {
			auto next = this->getElement(_pos.relativeLocation(_dir), result);
			switch (next) {
			case '#':
				cout << "hit wall at " << _pos.x << "," << _pos.y << endl;
				distance = 0;
				break;
			case '.':
				_pos = _pos.relativeLocation(_dir);
				break;
			case ' ':
				exit(0);
				break;
			default:
				cout << "finished at " << _pos.x << "," << _pos.y << endl;
				assert(0);
				break;
			}
		}
	}

	void wrapAround() {

	}

	xy getNextLocation() {
		bool result = false;
		auto next = this->getElement(_pos.relativeLocation(_dir), result);
		switch (next) {
		case '#':
			cout << "hit wall at " << _pos.x << "," << _pos.y << endl;
			distance = 0;
			break;
		case '.':
			_pos = _pos.relativeLocation(_dir);
			break;
		case ' ':
			exit(0);
			break;
		default:
			cout << "finished at " << _pos.x << "," << _pos.y << endl;
			assert(0);
			break;
		}
	}

	int distance
	xy _pos;
	Direction _dir = East;
	string path;
	const char* numbers = "0123456789";
	const char* letters = "RL";
};

#endif // MAP22A_H
