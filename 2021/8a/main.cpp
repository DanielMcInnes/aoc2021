#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace std;
int main()
{
	/*
	 * 0
	 * 1
	 * 2
	 * 3
	 * 4
	 * 5
	 * 6
	 * 7
	 * 8
	 * 9
	 *

*/
	vector<string> outputValue;
	vector<vector <string> > outputValues;
	string str;
	ifstream infile("data2");
	bool receivingOutput = false;
	int count = 0;

	while (infile >> str )
	{
		cout << "string: " << str <<  endl;
		if (str == "|")
		{
			receivingOutput = true;
			continue;
		}

		if (receivingOutput)
			outputValue.push_back(str);
		if (outputValue.size() == 4)
		{
			outputValues.push_back(outputValue);
			outputValue.clear();
			receivingOutput = false;
		}
	}

	for (auto out : outputValues)
	{
		cout << "output: ";
		for (auto digit : out)
		{
			cout << digit << " ";
			if ((digit.size() == 7) || (digit.size() == 4) || (digit.size() == 2) || (digit.size() == 3))
				count++;
		}
		cout << endl;
	}

	cout << "result: " << count << endl;
}
