#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include <QCoreApplication>
#include <QPoint>
#include <QLine>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<int> input;
    vector<int> row;
    vector<string> oxygen;
    vector<string> scrubber;
    string str;

    ifstream infile("data");
    QPoint* pointA = nullptr;
    QPoint* pointB = nullptr;

    class Vents : public map<int, map<int, int> >
    {
    public:
        int score()
        {
            int score = 0;

            for (auto i : *this)
            {
                for (auto j : i.second)
                {
                    if (j.second > 1)
                    {
                        //cout << i.first << ", " << j.first << " : " << j.second << endl;
                        score++;
                    }
                }
            }
            return score;
        }
        void addPoint(const int x, const int y)
        {
            (*this)[x][y]++;
            cout << "addPoint: " << x << ", " << y << " : " << (*this)[x][y] << endl;
        }
    };

    Vents vents;

    while (infile >> str )
    {
        if (str == "->")
        {
            //cout << "checking... " << str <<  endl;
        }
        else
        {
            string x(str.substr(0, str.find(",")));
            string y(str.substr(str.find(",") + 1, str.size()));
            cout << "x: " << x << " y:" << y << endl;
            if (pointA == nullptr)
            {
                pointA = new QPoint(stoi(x), stoi(y));
            }
            else
            {
                pointB = new QPoint(stoi(x), stoi(y));
                if ((pointA->x() == pointB->x()))
                {
                    int minY = pointA->y() < pointB->y() ? pointA->y() : pointB->y();
                    int maxY = pointA->y() > pointB->y() ? pointA->y() : pointB->y();
                    while (minY <= maxY)
                    {
                        vents.addPoint(pointA->x(), minY);
                        minY++;
                    }
                }
                else if (pointA->y() == pointB->y())
                {
                    int minX = pointA->x() < pointB->x() ? pointA->x() : pointB->x();
                    int maxX = pointA->x() > pointB->x() ? pointA->x() : pointB->x();
                    while (minX <= maxX)
                    {
                        vents.addPoint(minX, pointA->y());
                        minX++;
                    }
                }
                else if (abs(pointA->x() - pointB->x()) == abs(pointA->y() - pointB->y()))
                {
                    cout << "found diagonal" << endl;
                    vents.addPoint(pointA->x(), pointA->y());

                    while (pointA->x() != pointB->x())
                    {
                        pointA->setX(pointA->x() < pointB->x() ? pointA->x() + 1 : pointA->x() - 1);
                        pointA->setY(pointA->y() < pointB->y() ? pointA->y() + 1 : pointA->y() - 1);
                        vents.addPoint(pointA->x(), pointA->y());
                    }
                }

                delete pointA;
                delete pointB;
                pointA = nullptr;
                pointB = nullptr;
            }
        }
    }
    cout << "score: " << vents.score() << endl;

    return a.exec();
}
