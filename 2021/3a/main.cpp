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

   int i;

   int runningTotal[12];
   for (i = 0; i < 12; ++i)
   {
       runningTotal[i] = 0;
   }

   
   ifstream infile("data");
   while (infile >> str )
   {
      cout << "string: " << str << endl;

        for (int i = 0; i < 12; ++i)
        {
            if (str[i] == '0')
            {
                runningTotal[i]--;
            }
            else if (str[i] == '1')
            {
                runningTotal[i]++;
            }

        }
      /*
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
      */
   }
   for (i = 0; i < 12; ++i)
   {
      cout << i << ": " << runningTotal[i] << ", ";
      runningTotal[i] = runningTotal[i] < 0 ? 0 : 1;
   }
   cout << endl;
   for (i = 0; i < 12; ++i)
   {
      cout << runningTotal[i] ;
   }
   cout << endl;

   //cout << "Depth: " << depth << " x: " << x << " := " << x * depth << endl;
}
