#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

void print(map<int, map<int, bool> >& paper)
{
    cout << "=============================================================" << endl << endl;
    int xmax = 0;
    int ymax = 0;
    int xmin = 99999999999999;
    int ymin = 99999999999999;

    for (auto xpos : paper)
    {
        for (auto ypos : xpos.second)
        {
            if (ypos.second == true)
            {
                if (xpos.first > xmax)
                    xmax = xpos.first;
                if (xpos.first < xmin)
                    xmin = xpos.first;

                if(ypos.first > ymax)
                    ymax = ypos.first;
                if(ypos.first < ymin)
                    ymin = ypos.first;
            }
        }
    }
    for (int y = ymin; y <= ymax; ++y)
    {
        for (int x = xmin; x <= xmax; ++x)
        {
            if ((paper[x][y] == true))
            {
                //cout << x << "," << y;
                cout << "*";
            }
            else
            {
                cout << " ";
            }


        }
        cout << endl;
    }
    cout << "=============================================================" << endl << endl;

}
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
                if((paper[xpos.first][ypos.first] == true) && ypos.first >= foldAt)
                {
                    paper[xpos.first][ypos.first] = false;
                    int newYPos = foldAt - (ypos.first - foldAt);
                    cout << "newYPos:" << newYPos << endl;
                    cout << xpos.first << ", " << ypos.first << " is now: " << xpos.first << ", " << newYPos << endl;
                    paper[xpos.first][newYPos] = true;
                }
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
                if((paper[xpos.first][ypos.first] == true) && xpos.first >= foldAt)
                {
                    paper[xpos.first][ypos.first] = false;
                    int newXPos = foldAt - (xpos.first - foldAt);
                    paper[newXPos][ypos.first] = true;
                }
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
        cout << "str: " << str << endl;
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
    print(paper);


    for (auto it : instructions)
    {
        handleInstruction(paper, it);
        print(paper);
    }

    int xmax = 0;
    int ymax = 0;
    int xmin = 99999999999999;
    int ymin = 99999999999999;

    for (auto xpos : paper)
    {
        for (auto ypos : xpos.second)
        {
            if (xpos.first > xmax)
                xmax = xpos.first;
            if (xpos.first < xmin)
                xmin = xpos.first;

            if(ypos.first > ymax)
                ymax = ypos.first;
            if(ypos.first < ymin)
                ymin = ypos.first;
        }
    }



    int xrange = xmax - xmin;
    int yrange = ymax - ymin;
    cout << "xmin: " << xmin << " xmax: " << xmax << " ymin: " << ymin << " ymax: " << ymax << " xrange: " << xrange << " yrange: " << yrange << endl;
}
