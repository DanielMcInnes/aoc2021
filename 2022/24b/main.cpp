#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
	Grid grid("../input2");
	int counter = 0;
	while (grid._foundExit == false) {
	//for (int i = 0; i < 5; ++i) {
		cout << endl << "Minute " << counter << ":" << endl;
		grid.process();
		grid.print();
		counter++;
	}
	cout << "Found exit after " << counter << " iterations" << endl;

	counter = 0;

	cout << "clearing expeditions" << endl;
	grid.clearExpeditions(true, true);
	grid.print();
	return 0;
}
