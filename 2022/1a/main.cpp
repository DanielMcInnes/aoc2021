#include <QCoreApplication>

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	map<int, int> elfCalories;
	int maxCaloriesElfIndex = 0;


	// open file
	ifstream inputFile("../input");

	// test file open
	if (inputFile) {
		int elf = 0;      // count number of items in the file
		int calories = 0;
		string line;
		while (getline(inputFile, line))
		{
			if (line == "")
			{
				cout << "elf: " << elf << " calories: " << elfCalories[elf] << endl;
				elf++;
				calories = 0;
			}
			else
			{
				calories = atoi(line.c_str());
				elfCalories[elf] += calories;
			}
		}
	}

	cout << "elf #" << result->first << " has the most calories: " << result->second << endl;

	inputFile.close();



	return a.exec();
}
