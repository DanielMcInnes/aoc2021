#include <QCoreApplication>

#include <algorithm>
#include <vector>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Grid grid("../input4");
	grid.process();

	return a.exec();
}
