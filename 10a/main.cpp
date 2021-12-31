#include <QCoreApplication>
#include <QStringList>
#include <QtQml/qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QVariant>
#include <QPoint>
#include <QMetaType>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <stdlib.h>
#include <utility>

using namespace std;

bool deletePairs(string& str, const vector<string> pairs) {
	bool retval = false;

	for (auto pair : pairs) {
		auto idx = str.find(pair);
		if (idx != string::npos) {
			str.erase(idx, pair.size());
			retval = true;
		}
	}

	return retval;
}
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	int score = 0;
	string str;
	vector<string> lines;
	map<char, char> mapCloseOpen {
		{')', '('},
		{'}', '{'},
		{']', '['},
		{'>', '<'},
	};
	map<char, int> scores {
		{')', 3},
		{'}', 1197},
		{']', 57},
		{'>', 25137},
	};
	const vector<string> pairs{"()", "<>", "{}", "[]"};
	const vector<string> closingChars{")", ">", "}", "]"};
	const vector<char> openingChars{'(', '<','{', '[' };

	ifstream infile("data");
	while (infile >> str)
	{
		lines.push_back(str);
	}
	for(string str : lines) {
		cout << "str: " << str << endl;
		while (str.size() > 0) {
			bool finished = false;
			int counter = 0;
			int pos = 0;
			for (auto closing : closingChars) {
				if ((pos = str.find(closing)) == string::npos) {
					counter++;
				}
				else {
					if ((find(openingChars.begin(), openingChars.end(), (str[pos-1])) != openingChars.end()) &&
							(str[pos - 1] != mapCloseOpen[str[pos]])
							) {
						cout << "Invalid string! " << str << " at position: " << pos << endl;
						score += scores[str[pos]];
						finished = true;
						break;
					}
				}
			}
			if (finished) {
				break;
			}
			if (counter == closingChars.size()) {
				cout << "No more closing chars in this string: " << str << endl;
				finished = true;
				break;
			}
			while (deletePairs(str, pairs)) {
				cout << "deleted" << endl;
			}

			cout << "str: " << str << endl;
		}
	}
	cout << "score: " << score << endl;
	return a.exec();
}
