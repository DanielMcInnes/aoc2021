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

map<int, map<int, int> > grid;
int flashes = 0;


void printgrid() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.size(); ++j) {
			cout << grid[j][i];
		}
		cout << endl;
	}
	cout << endl;
}
void flash(int x, int y) {
	flashes++;
	if (x > 0) { //left
		grid[x-1][y]++;
		if (grid[x-1][y] == 10) {
			flash(x-1, y);
		}
	}
	if ((x > 0) && y > 0) { //top left
		grid[x-1][y-1]++;
		if (grid[x-1][y-1] == 10) {
			flash(x-1, y-1);
		}
	}
	if (y > 0) { //top
		grid[x][y-1]++;
		if (grid[x][y-1] == 10) {
			flash(x, y-1);
		}
	}
	if ((x < (grid.size() - 1)) && y > 0) { //top right
		grid[x+1][y-1]++;
		if (grid[x+1][y-1] == 10) {
			flash(x+1, y-1);
		}
	}
	if ((x < (grid.size() - 1))) { //right
		grid[x+1][y]++;
		if (grid[x+1][y] == 10) {
			flash(x+1, y);
		}
	}
	if ((x < (grid.size() - 1)) && y < (grid.size() - 1)) { //bottom right
		grid[x+1][y+1]++;
		if (grid[x+1][y+1] == 10) {
			flash(x+1, y+1);
		}
	}
	if (y < (grid.size() - 1)) { //bottom
		grid[x][y+1]++;
		if (grid[x][y+1] == 10) {
			flash(x, y+1);
		}
	}
	if ((x > 0) && y < (grid.size() - 1)) { //bottom left
		grid[x-1][y+1]++;
		if (grid[x-1][y+1] == 10) {
			flash(x-1, y+1);
		}
	}
}
void step() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.size(); ++j) {
			grid[j][i]++;
			if (grid[j][i] == 10) {
				flash(j, i);
			}
		}
	}
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.size(); ++j) {
			if (grid[j][i] > 9) {
				grid[j][i] = 0;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	string str;
	ifstream infile("data");
	int x, y;
	while (infile >> str)
	{
		cout << "str: " << str << endl;
		for (auto ch : str) {
			grid[x][y] = ch - '0';
			x++;
		}
		x = 0;
		y++;
	}
	cout << endl;
	for (int i = 0; i < 100; ++i) {
		step();
		printgrid();
	}

	cout << "flashes: "<< flashes << endl;
	return a.exec();
}
