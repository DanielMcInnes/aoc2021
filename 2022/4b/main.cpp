#include <QCoreApplication>

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
int linenumber = 1;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ifstream inputFile("../input");
	int score = 0;

	struct Area{
		int begin = 0;
		int end = 0;
		bool contains(const Area& other) {
			bool b1 = begin <= other.end;
			bool b2 = end >= other.begin;
			bool retval = b1 && b2;
			if (retval) {
				cout << "line: " << linenumber << " found a match " << begin << "-" << end << ", " << other.begin << "-" << other.end << endl;
			}
			return (retval);
		}
	};

	if (inputFile) {
		string line;
		while (getline(inputFile, line))
		{
			Area a1, a2;
			a1.begin = atoi(line.substr(0, (line.find('-'))).c_str());
			a1.end = atoi(line.substr(line.find('-') + 1, line.find(',') - 1).c_str());
			a2.begin = atoi(line.substr(line.find(',') + 1, (line.rfind('-'))).c_str());
			a2.end = atoi(line.substr(line.rfind('-') + 1).c_str());
			if (a1.contains(a2) || a2.contains(a1)) {
				score++;
			}
			cout << "line: " << linenumber << " a1.begin: " << a1.begin << " a1.end: " << a1.end << " a2.begin: " << a2.begin << " a2.end: " << a2.end << " score: " << score << endl << endl;
			linenumber++;
		}
	}
	cout << "score: " << score << endl;
	return a.exec();
}
