#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	int total = 0;
	cout << "blah" << endl;
	ifstream inputFile("../input");
	const string digits("0123456789");

	if (inputFile) {
		string line;
		while (getline(inputFile, line)) {
			size_t first = line.find_first_of(digits);
			string calibrationValue;
			if (first != string::npos) {
				calibrationValue = line.substr(first, 1);
				cout << "first:" << calibrationValue;
			}

			size_t last = line.find_last_of(digits);
			if (last != string::npos) {
				cout << " last:" << line.substr(last, 1);
				calibrationValue.push_back(line[last]);
			}

			cout << " : " << stoi(calibrationValue);
			total += stoi(calibrationValue);
			cout << endl;
		}
		inputFile.close();
	}

	cout << "result: " << total << endl;

	return 0;
}
