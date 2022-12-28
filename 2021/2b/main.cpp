#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
   int x = 0;
   int depth = 0;
   int aim = 0;

   string str;
   int distance;
   
   ifstream infile("data");
   while (infile >> str >> distance)
   {
      //cout << "string: " << str << " distance: " << distance << endl;
      if (str == "up")
      {
         //cout << "string: " << str << " distance: " << distance << endl;
         aim -= distance;
      }
      else if (str == "down")
      {
         aim += distance;
      }
      else if (str == "forward")
      {
          x += distance;
          depth += aim * distance;
      }
   }
   cout << "Depth: " << depth << " x: " << x << " := " << x * depth << endl;
}
