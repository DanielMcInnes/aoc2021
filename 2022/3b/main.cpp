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
		string rucksack;
		vector<string> rucksacks;
		int priority;
		while (getline(inputFile, rucksack))
		{
			string compartmentA(rucksack.substr(0, rucksack.length()/2));
			string compartmentB(rucksack.substr(rucksack.length()/2));
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
			cout << rucksack << " compartmentA: " << compartmentA << " compartmentB: " << compartmentB << " items: " << items << " priority: " << priority <<  endl;
			items.clear();
			//score += priority;
			rucksacks.push_back(rucksack);
			if (rucksacks.size() == 3) {
				for (auto &ch : rucksacks[0]) {
					if (rucksacks[1].find(ch) != string::npos && rucksacks[2].find(ch) != string::npos) {
						cout << "Badge: " << ch << endl;
						priority = ch;
						if (priority >= 'a') {
							priority -= 'a';
							priority += 1;
						} else {
							priority -= 'A';
							priority += 27;
						}
						score += priority;
						break;
					}
				}
				rucksacks.clear();
			}
		}
		cout << "score: " << score << endl;
	}
	return a.exec();
}
