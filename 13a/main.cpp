#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace std;


int countDots(map<int, map<int, bool> >& paper)
{
    int count = 0;
    for (auto xpos : paper)
    {
        for (auto ypos : xpos.second)
        {
            if (ypos.second == true)
            {
                count++;
            }
        }
    }
    return count;
}

void handleInstruction(map<int, map<int, bool> >& paper, string& instruction)
{
    bool yFold = (instruction[0] == 'y');

    const int foldAt = stoi(instruction.substr(instruction.find("=") + 1));

    if (yFold)
    {
        cout << "yFold:" << yFold << " instruction: " << instruction << " foldAt: " << foldAt << endl;
        for (auto xpos : paper)
        {
            for (auto ypos : xpos.second)
            {
                paper[xpos.first][ypos.first] = false;
                int newYPos = foldAt - (ypos.first - foldAt);
                paper[xpos.first][newYPos] = true;
            }
        }
    }
    else
    {
        cout << "yFold:" << yFold << " instruction: " << instruction << " foldAt: " << foldAt << endl;
        for (auto xpos : paper)
        {
            for (auto ypos : xpos.second)
            {
                paper[xpos.first][ypos.first] = false;
                int newXPos = foldAt - (xpos.first - foldAt);
                paper[newXPos][ypos.first] = true;
            }
        }
    }
}


int main()
{
    map<int, map<int, bool> > paper;
    string str, instruction;
    vector<string> instructions;
    int x, y;
    bool parsingInstructions = false;

    ifstream infile("data");
    while (infile >> str)
	{
        if (str == "fold")
        {
            parsingInstructions = true;
        }

        if (!parsingInstructions)
        {
            cout << "str: " << str << endl;
            x = stoi(str.substr(0, str.find(",", 0)));

            y = stoi(str.substr(str.find(',', 0) + 1, str.size()));
            cout << " x: " << x << " y: " << y << endl;
            paper[x][y] = true;
        }
        if (parsingInstructions)
        {
            if ((str == "fold") || (str == "along"))
                continue;

            instruction = str;

            cout << "instructions: " << instruction << endl;
            instructions.push_back(instruction);
        }
	}

    for (auto it : instructions)
    {
        handleInstruction(paper, instruction);
    }

    for (auto it)
}
