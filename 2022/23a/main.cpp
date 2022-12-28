
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "grid.h"

using namespace std;


int main(int argc, char *argv[])
{
	Grid oldgrid("../input");
	Grid grid("../input");
	for (int i = 0; ; ++i) {
		bool elfMoved = grid.process();
		cout << "== End of Round " << i+1 << " ==" << endl;
		if (!elfMoved) {
			break;
		}
	}
	grid.print();
	return 0;
}
