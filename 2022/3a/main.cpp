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

	ifstream inputFile("../input");
	int score = 0;

	if (inputFile) {
		string line;
		int priority;
		while (getline(inputFile, line))
		{
			string compartmentA(line.substr(0, line.length()/2));
			string compartmentB(line.substr(line.length()/2));
			string items;

			for (auto &ch : compartmentA) {
				if (compartmentB.find(ch) != string::npos) {
					items += ch;
					priority = ch;
					if (priority >= 'a') {
						priority -= 'a';
						priority += 1;
					} else {
						priority -= 'A';
						priority += 27;
					}
					continue;
				}
			}
			cout << line << " compartmentA: " << compartmentA << " compartmentB: " << compartmentB << " items: " << items << " priority: " << priority <<  endl;
			items.clear();
			score += priority;
		}
		cout << "score: " << score << endl;
	}
	return a.exec();
}
