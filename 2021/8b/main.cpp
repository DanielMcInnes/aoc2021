#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace std;

enum Segment{
	a,b,c,d,e,f,g
};

vector<string> outputValue;
vector<string> inputValue;
vector <string> outputValues;
vector<vector <string> > inputValues;
map<string, int> mapStringDigit;
map<int, string> mapDigitString;
map<string, Segment> mapStringToSegment;
map<Segment, string> mapSegmentToString;
int runningTotal = 0;

void mapInputToOutput()
{
	for (auto& it : inputValue)
	{
		sort(it.begin(), it.end());
		int size = it.size();
		switch (size)
		{
		case 2:
			mapStringDigit[it] = 1;
			mapDigitString[1] = it;
			break;
		case 3:
			mapStringDigit[it] = 7;
			mapDigitString[7] = it;
			break;
		case 4:
			mapStringDigit[it] = 4;
			mapDigitString[4] = it;
			break;
		case 7:
			mapStringDigit[it] = 8;
			mapDigitString[8] = it;
			break;
		}
	}
	inputValues.push_back(inputValue);

	// calculate segment A
	{
		string str7(mapDigitString[7]);
		string str1(mapDigitString[1]);
		cout << "str1: " << str1 << " str7: " << str7 << endl;
		for (auto segment : str1)
		{
			str7.erase(str7.find(segment), 1);
		}
		cout << "segment a: " << str7 << endl;
		mapStringToSegment[str7] = a;
		mapSegmentToString[a] = str7;
	}

	// calculate segment C, 6
	{
		string remainder;
		for (auto it : inputValue)
		{
			if (it.size() == 6) // must be 0, 6, or 9
			{
				string str8(mapDigitString[8]);
				string temp = it;
				for (auto ch : it)
				{
					str8.erase(str8.find(ch), 1);
				}
				remainder = str8;

				string str1(mapDigitString[1]);

				if (find(str1.begin(), str1.end(), remainder[0]) != str1.end())
				{
					mapDigitString[6] = it;
					mapStringDigit[it] = 6;
					mapStringToSegment[it] = c;
					mapSegmentToString[c] = remainder ;
					cout << "segment c: " << remainder << endl;
				}
			}
		}
	}

	// calculate segment f
	{
		string str1 = mapDigitString[1];
		cout << "str1: " << str1 << " mapSegmentToString[c]: " << mapSegmentToString[c] << endl;
		str1.erase(str1.find(mapSegmentToString[c]), 1);
		cout << "segment f: " << str1 << endl;
	}

	// calculate segment e, D, 0, 9
	{
		for (auto it : inputValue)
		{
			if ((it.size() == 6) && (it != mapDigitString[6])) // must be 0 or 9
			{
				string remainder(mapDigitString[8]);
				for (auto ch : it)
				{
					remainder.erase(remainder.find(ch), 1);
				}
				string str4(mapDigitString[4]);
				if (str4.find(remainder) == string::npos)
				{
					cout << "segment e: " << remainder << endl;
					mapSegmentToString[e] = remainder;
					mapStringToSegment[remainder] = e;
					mapDigitString[9] = it;
					mapStringDigit[it] = 9;
				}
				else
				{
					cout << "segment d: " << remainder << endl;
					mapSegmentToString[d] = remainder;
					mapStringToSegment[remainder] = d;
					cout << "str0: " << it << endl;
					mapDigitString[0] = it;
					mapStringDigit[it] = 0;
				}
			}
		}
	}

	// calculate 5
	{
		string str5(mapDigitString[6]);
		str5.erase(str5.find(mapSegmentToString[e]), 1);
		mapDigitString[5] = str5;
		mapStringDigit[str5] = 5;
		cout << "str5: " << str5 << endl;
	}

	// calculate 2, 3
	{
		for (auto it : inputValue)
		{
			if ((it.size() == 5) && (it != mapDigitString[5])) // must be 2 or 3
			{
				if (it.find(mapSegmentToString[e]) == string::npos)
				{
					cout << "str3: " << it << endl;
					mapDigitString[3] = it;
					mapStringDigit[it] = 3;
				}
				else
				{
					cout << "str2: " << it << endl;
					mapDigitString[2] = it;
					mapStringDigit[it] = 2;
				}
			}
		}
	}

	inputValue.clear();
	for (auto& it : mapDigitString)
	{
		sort(it.second.begin(), it.second.end());
		cout << "mapping: " << it.first << " = " << it.second << endl;
	}
}

int main()
{
	string strResult;
	int result = 0;

	string str;
	ifstream infile("data");

	bool receivingOutput = false;
	int count = 0;
	map<int, string> decoded;

	while (infile >> str )
	{
		cout << "string: " << str <<  endl;
		if (str == "|")
		{
			receivingOutput = true;
			continue;
		}

		if (receivingOutput)
		{
			outputValue.push_back(str);
			if (outputValue.size() == 4)
			{
				for (auto it : outputValue)
				{
					outputValues.push_back(it);
				}
				if (inputValue.size() == 10) // we know enough to map input to output
				{
					mapInputToOutput();

					for (auto it : outputValues)
					{
						sort(it.begin(), it.end());
						cout << "output: " << it << endl;
						for (auto digit : mapDigitString)
						{
							if (it == digit.second)
							{
								cout << "digit: " << digit.first << endl;
								strResult.append(to_string(digit.first));
								if (strResult.size() == 4)
								{
									cout << "decoded: " << stoi(strResult) << endl;
									result = stoi(strResult);
									strResult.clear();
								}
							}
						}
					}
					cout << "result: " << result << endl << endl;
					runningTotal += result;
					mapDigitString.clear();
					mapStringDigit.clear();
					mapSegmentToString.clear();
					mapStringToSegment.clear();
					inputValue.clear();
					inputValues.clear();
					outputValue.clear();
					outputValues.clear();
					receivingOutput = false;
				}

			}
		}
		else
		{
			inputValue.push_back(str);
		}
	}


	cout << "total: " << runningTotal << endl;



}
