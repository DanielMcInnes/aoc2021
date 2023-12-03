#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using namespace std;

struct game {
	int id;
	int red;
	int blue;
	int green;
};

int main()
{
	ifstream inputFile("input");
	const game reference{.id = 0, .red = 12, .blue = 14, .green = 13};
	if (inputFile) {
		string line;
		while (getline(inputFile, line)) {
			cout << "line: " << line << endl;
		}
		inputFile.close();
	}
}
