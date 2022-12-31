#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
	Grid grid("../input");
	int counter = 0, answerA = 0, answerB = 0;
	while (grid._foundExit == false) {
		cout << endl << "Minute " << counter << ":" << endl;
		grid.process();
		grid.print();
		counter++;
	}
	cout << "Found exit after " << counter << " iterations" << endl;
	answerA = counter;

	cout << "clearing expeditions" << endl;
	grid.clearExpeditions(true, false);
	grid.print();
	grid._foundEntrance = false;
	while (grid._foundEntrance == false) {
		cout << endl << "Minute " << counter << ":" << endl;
		grid.process();
		grid.print();
		counter++;
	}
	cout << "Found entrance after " << counter << " iterations" << endl;

	cout << "clearing expeditions" << endl;
	grid.clearExpeditions(false, true);
	grid.print();
	grid._foundExit = false;
	while (grid._foundExit == false) {
		cout << endl << "Minute " << counter << ":" << endl;
		grid.process();
		grid.print();
		counter++;
	}
	cout << "Found exit after " << counter << " iterations" << endl;


	return 0;
}
