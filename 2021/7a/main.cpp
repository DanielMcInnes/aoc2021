#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include <QCoreApplication>
#include <QPoint>
#include <QLine>

#include "csv_istream_iterator.h"

vector<int> input;

int calcCost(int pos)
{
	int cost;

	for (auto position : input)
	{
		int distance = abs(pos - position);
		int stepCost = 1;
		while (distance > 0)
		{
			cost += stepCost;
			stepCost++;
			distance--;
		}
	}
	cout << "move all to " << pos << " costs " << cost << endl;
	return cost;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	map<int, int> density;
	string str;
	uint64_t total;
	int count;

	int fuel = 0;

	ifstream infile("data");
	copy( csv_istream_iterator<int>( infile ),
		  csv_istream_iterator<int>(),
		  insert_iterator< vector<int> >( input, input.begin() ) );

	int minFuel = calcCost(input[0]);
	int destination = 0;
	int minPos = input[0];
	int maxPos = input[0];


	for (auto pos : input)
	{
		if (pos < minPos)
			minPos = pos;
		if (pos > maxPos)
			maxPos = pos;
	}

	for (int i = minPos; i < maxPos; ++i)
	{
		fuel = calcCost(i);
		if (fuel < minFuel)
		{
			minFuel = fuel;
			destination = i;
		}
	}

	cout << "destination: " << destination << " fuel: " << minFuel << endl;


	return 0; //a.exec();
}
