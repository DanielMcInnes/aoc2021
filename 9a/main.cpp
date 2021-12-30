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
using namespace std;

vector< vector<int> > heightmap;
int width;
int height;

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
			}
		}
	}

	cout << "risk: " << risk << endl;

	return a.exec();
}
