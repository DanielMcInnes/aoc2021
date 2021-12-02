#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include <QCoreApplication>
#include <QPoint>
#include <QLine>

#include "csv_istream_iterator.h"

using namespace std;

uint64_t calcFish(int days, int state, uint64_t& result)
{
    while (days > 0)
    {
        days--;
        state--;
        if (state == -1)
        {
            result++;
            state = 6;
            calcFish(days, 8, result);
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<int8_t> input;
    string str;
    int days = 256;

    ifstream infile("data");
    copy( csv_istream_iterator<int>( infile ),
          csv_istream_iterator<int>(),
          insert_iterator< vector<int8_t> >( input, input.begin() ) );
    uint64_t fishCount = input.size(); // we start with this many fish

    int fishId = 0;

    cout << "input size: " << input.size() << endl;
    vector<int8_t> possibleInitialStates = {1,2,3,4,5};
    vector<uint64_t> progeny; // {6206821032, 5617089147, 5217223241, 4726100873, 4368232008 };

    // fish only start in 1 of 5 states. For each of those states, calculate how many progeny will spawn.
    for (auto it = possibleInitialStates.begin(); it != possibleInitialStates.end(); ++ it)
    {
        uint64_t temp = 0;
        cout << "calculating fishId: " << fishId << " state: " << (int)*it;
        uint64_t singleResult = calcFish(days, *it, temp);
        cout << " result: " << singleResult << endl;
        fishId++;
        cout << (int)*it << endl;
        progeny.push_back(singleResult);
    }

    // for each fish in the input list (~600), given its initial state, add how many progeny it would spawn.
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        fishCount += progeny[*it - 1];
    }
    cout << "result: " << fishCount << endl;

    return 0;
}
