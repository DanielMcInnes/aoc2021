#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
	Grid grid("../input3");
	for (int i = 0; i < 1; ++i) {
		grid.process();
		grid.print();
	}
	return 0;
}
