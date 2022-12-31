#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
	Grid grid("../input");
	int counter = 0;
	while (grid._foundExit == false) {
	//for (int i = 0; i < 5; ++i) {
		cout << endl << "Minute " << counter << ":" << endl;
		grid.process();
		grid.print();
		counter++;
	}
	cout << "Found exit after " << counter << " iterations" << endl;
	return 0;
}
