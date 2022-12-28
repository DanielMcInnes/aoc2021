#include <QCoreApplication>

#include <algorithm>
#include <vector>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Grid grid("../input2");
	for (int i = 0; i < 10; ++i) {
		grid.process();
	}

	return a.exec();
}
