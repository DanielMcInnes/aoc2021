#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 56069
int main(int argc, char *argv[])
{
	int total = 0;
	ifstream inputFile("../input");
	vector< pair<string, int> > digits{{"0", 0},{"1", 1},{"2", 2},{"3", 3},{"4", 4},{"5", 5},{"6", 6},{"7", 7},{"8", 8},{"9", 9},
							 {"zero", 0}, {"one", 1},{"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7},{"eight", 8}, {"nine", 9}
					};

	if (inputFile) {
		string line;
		while (getline(inputFile, line)) {
			cout << "line: " << line << endl;
			map<size_t, int> first;
			map<size_t, int> last;
			for (const auto& digit : digits) {
				cout << "	digit: " << digit.first << " length: " << digit.first.length() << endl;
				size_t index = line.find(digit.first.c_str(), 0, digit.first.length());
				if (index != string::npos) {
					cout << "		searching for:" << digit.first << " first index: " << index << ":" << digit.second	;
					first[index] = digit.second;
				}

				index = line.rfind(digit.first.c_str(), line.length() - 1, digit.first.length());
				if (index != string::npos) {
					cout << " second index: " << index << ":" << digit.second << endl;
					last[index] = digit.second;
				}
			}

			int result = ((first.begin()->second) * 10) + (last.rbegin()->second);
			cout << " result: " <<  first.begin()->second << " " << last.rbegin()->second << ":" << result << endl;
			total += result;
		}
		inputFile.close();
	}

	cout << "total: " << total << endl;

	return 0;
}
