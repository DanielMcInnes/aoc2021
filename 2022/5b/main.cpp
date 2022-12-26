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
	map<int, vector <string> > stacks;

	if (inputFile) {
		string line;
		while (getline(inputFile, line))
		{
			if (line.find("move") == string::npos && line.find("1") == string::npos) {
				int stack = 1;
				for (int i = 1; i < line.length(); i +=4) {
					string crate = line.substr(i, 1);
					if (crate != " ") {
						cout << "adding " << crate << " to stack " << stack << endl;
						stacks[stack].push_back(crate);
					}
					stack++;
				}
			}
			else if (line.find("move") != string::npos) {
				cout << line << endl;

				int count = atoi(line.substr(5, line.find("from") -1).c_str());
				int fromStack = atoi(line.substr(line.find("from") + 5, line.find("to") - 1).c_str());
				int toStack = atoi(line.substr(line.find("to") + 3).c_str());

				cout << " count: " << count << " from: " << fromStack << " to: " << toStack << endl;

				for (int i = 0; i < count; ++i) {
					auto& dest = stacks[toStack];
					auto& source = stacks[fromStack];
					auto moving = source.begin() + count - i - 1;
					auto topdest = dest.front();
					cout << "	pushing " << *moving << " on top of " << topdest << endl;
					dest.insert(dest.begin(), *moving);
					source.erase(moving);
				}
			}
		}
		cout << "top crates: ";
		for (auto& stack : stacks) {
				cout << stack.second.front();
		}
	}
	cout << endl;
	return a.exec();
}
