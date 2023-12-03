#include <iostream>

#include "map22a.h"

using namespace std;

int main()
{
	map22a<int, int, char> map("../input2");
	cout << "path: " << map.path << endl;
	map.process();
	return 0;
}
