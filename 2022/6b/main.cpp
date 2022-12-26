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

	const int bufferSize = 14;

	ifstream inputFile("../input");
	int count = 0;
	map<int, vector <string> > stacks;

	if (inputFile) {
		string line;
		while (getline(inputFile, line))
		{
			cout << "line: " << line << endl;
			vector<char> buffer;
			for (auto& ch : line) {

				count++;
				buffer.push_back(ch);
				if (buffer.size() > bufferSize) {
					buffer.erase(buffer.begin());
					cout << "buffer: " << string(buffer.begin(), buffer.end()) << endl;
				}
				if (buffer.size() == bufferSize) {
					bool found = true;
					for (char& c : buffer) {
						if (std::count(buffer.begin(), buffer.end(), c) > 1) {
							found = false;
						}
					}
					if (found) {
						cout << "found after " << count << " characters" << endl;
						break;
					}
				}
			}
		}
	}
	return a.exec();
}
