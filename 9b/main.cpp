#include <QCoreApplication>
#include <QStringList>
#include <QtQml/qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QVariant>
#include <QPoint>
#include <QMetaType>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <stdlib.h>
#include <utility>

using namespace std;

vector< vector<int> > heightmap;

typedef pair<int, int> Point;
class Lowpoint;
vector< Lowpoint > lowpoints;

int width;
int height;

class Lowpoint : public Point {
public:
	Lowpoint(int x, int y) : Point(x,y){
		Point p(x, y);
	}
	bool isPointInBasin(Point p) {
		if(heightmap[p.second][p.first] == 9) {
			return false;
		}
		return true;
	}

	void addPointToBasin(Point p) {
		if (find(_basinPoints.begin(), _basinPoints.end(), p) != _basinPoints.end()) {
			return;
		}
		//cout << "addPointToBasin: " << p.first << ", " << p.second << endl;
		int x(p.first);
		int y(p.second);
		_basinPoints.push_back(p);

		if (x > 0) {
			Point p2(x-1, y);
			if (isPointInBasin(p2)) {
				addPointToBasin(p2);
			}
		}
		if (x < (width - 1)) {
			Point p2(x+1, y);
			if (isPointInBasin(p2)) {
				addPointToBasin(p2);
			}
		}
		if (y > 0) {
			Point p2(x, y-1);
			if (isPointInBasin(p2)) {
				addPointToBasin(p2);
			}
		}
		if (y < (height - 1)) {
			Point p2(x, y+1);
			if (isPointInBasin(p2)) {
				addPointToBasin(p2);
			}
		}
	}


	vector< Point > _basinPoints;
};


bool isLowest(const int x, const int y)
{
	if (x > 0) {
		if (heightmap[y][x-1] <= heightmap[y][x] ) return false;
	}
	if (x < (width - 1)) {
		if (heightmap[y][x+1] <= heightmap[y][x] ) return false;
	}
	if (y > 0) {
		if (heightmap[y-1][x] <= heightmap[y][x] ) return false;
	}
	if (y < (height - 1)) {
		if (heightmap[y+1][x] <= heightmap[y][x] ) return false;
	}
	return true;
}

bool sorter(Lowpoint& lhs, Lowpoint& rhs ) {
	bool retval = lhs._basinPoints.size() < rhs._basinPoints.size();
	cout << "sorter: returning: " << retval << endl;
	return retval;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	string str;

	ifstream infile("data");
	while (infile >> str)
	{
		vector<int> heights;
		cout << "str: " << str << endl;
		for (auto ch : str) {
			heights.push_back(atoi(&ch));
		}
		heightmap.push_back(heights);
	}

	for (auto heights : heightmap) {
		for (auto height : heights) {
			cout << height;
		}
		cout << endl;
	}

	width = (heightmap[0].size());
	height = (heightmap.size());

	int risk = 0;

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			if (isLowest(x, y)) {
				cout << x << ", " << y << " is lowest. " << heightmap[y][x] << endl;
				risk += (heightmap[y][x] + 1);
				lowpoints.push_back(Lowpoint(x, y));
			}
		}
	}

	cout << "risk: " << risk << endl;

	for (auto& lowpoint : lowpoints) {
		Point p;
		p.first = lowpoint.first;
		p.second = lowpoint.second;
		lowpoint.addPointToBasin(p);
		cout << "lowpoint: " << lowpoint.first << ", " << lowpoint.second <<
				" basin size: " << lowpoint._basinPoints.size() << endl;
	}
	sort(lowpoints.begin(), lowpoints.end(), sorter);

	for (auto lowpoint : lowpoints) {
		cout << "sorted: lowpoint: " << lowpoint.first << ", " << lowpoint.second << " basin size: " << lowpoint._basinPoints.size() << endl;
	}
	int basinSize = 0;

	basinSize = lowpoints[lowpoints.size() - 1]._basinPoints.size() *
			lowpoints[lowpoints.size() - 2]._basinPoints.size() *
			lowpoints[lowpoints.size() - 3]._basinPoints.size();

	cout << "basinSize: " << basinSize << endl;


	return a.exec();
}
