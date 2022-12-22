#include <QCoreApplication>

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	map<int, int> elfCalories;

	// open file
	ifstream inputFile("../input");

	// test file open
	if (inputFile) {
		int elf = 1;      // count number of items in the file
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
	auto result = max_element(elfCalories.begin(), elfCalories.end(), [](auto a, auto b) { return a.second < b.second; });

	cout << "elf #" << result->first << " has the most calories: " << result->second << endl;

	inputFile.close();


	int topThreeCalories = 0;
	for (int i = 0; i < 3; ++i) {
		auto max = max_element(elfCalories.begin(), elfCalories.end(), [](auto a, auto b) { return a.second < b.second; });
		topThreeCalories += max->second;
		elfCalories.erase(max);
	}

	cout << "top three: " << topThreeCalories << endl;




	return a.exec();
}
