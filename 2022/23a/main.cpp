#include <QCoreApplication>

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Grid grid("../input");
	for (int i = 0; i < 10; ++i) {
		grid.process();
		cout << "== End of Round " << i+1 << " ==" << endl;
	}

	grid.print();
	exit(0);
	return a.exec();
}
