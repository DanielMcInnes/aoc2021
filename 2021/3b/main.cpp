#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
   vector<string> input;
   vector<string> oxygen;
   vector<string> scrubber;
   string str;
   int i;
   int checking = 0;

   ifstream infile("data");

   while (infile >> str )
   {
      input.push_back(str);
   }
   oxygen = input;
   scrubber = input;


   while(oxygen.size() > 1)
   {
      int total = 0;
      for(string ox : oxygen)
      {
         total += ox[checking] == '1' ? 1 : -1;
      }
      char keeping = total >= 0 ? '1' : '0';

      oxygen.erase(std::remove_if(
         oxygen.begin(), oxygen.end(), [keeping, checking](string& str) { return str[checking] != keeping; }), oxygen.end()
         );

      checking++;
   }

   int oxygenVal = stoi(oxygen[0], 0, 2);
   cout << "oxygen: " << oxygen[0] <<  " :" << oxygenVal << endl;

   checking = 0;

   while(scrubber.size() > 1)
   {
      int total = 0;
      for(string ox : scrubber)
      {
         total += ox[checking] == '1' ? 1 : -1;
      }
      char keeping = total >= 0 ? '0' : '1';

      scrubber.erase(std::remove_if(
         scrubber.begin(), scrubber.end(), [keeping, checking](string& str) { return str[checking] != keeping; }), scrubber.end()
         );

      checking++;
   }

   int scrubberVal = stoi(scrubber[0], 0, 2);
   cout << "scrubber: " << scrubber[0] << " :" << endl;

   cout << "life support rating: " << oxygenVal * scrubberVal << endl;
}
