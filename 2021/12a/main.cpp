#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace std;
map<string, vector<string> > connections;
vector< vector<string> > paths;

void addNewSteps(vector<string>& path, const string& startPoint)
{
	cout << "addNewSteps: startPoint: " << startPoint << "." << endl;
	path.push_back(startPoint);
	if ((startPoint == "end") && find(paths.begin(), paths.end(), path) == paths.end())
	{
		paths.push_back(path);
		return;
	}

	vector<string>& possibleNextSteps(connections[startPoint]);
	for (auto step : possibleNextSteps)
	{
		if (isupper(step[0]) || find(path.begin(), path.end(), step) == path.end())
		{
			vector<string> newPath(path);
			addNewSteps(newPath, step);
		}
	}
}

int main()
{
   string str;


   ifstream infile("data");
   while (infile >> str )
   {
	  cout << "string: " << str <<  endl;
	  string strA = str.substr(0, str.find("-"));
	  string strB = str.substr(str.find("-") + 1, str.size() - 1);
	  connections[strA].push_back(strB);
	  connections[strB].push_back(strA);
	  cout << "str: " << strA << ". connections[" << strA << "].size(): " << connections[strA].size() << " strB: " << strB << " << " << " paths.size: " << connections.size() << endl;
   }

   for (auto it = connections.begin(); it != connections.end(); ++it)
   {
	   for (auto j : it->second)
	   {
		   cout << "connection: " << it->first << " - " << j << endl;
		   if (it->first == "start")
		   {
			   for (auto next : it->second)
			   {
				   vector<string> newPath;
				   newPath.push_back(it->first);
				   addNewSteps(newPath, next);
			   }
		   }
	   }
   }

   for (auto it : paths)
   {
	   for (auto str: it)
	   {
		   cout << str << " ";
	   }
	   cout << endl;
   }
   cout << "result: " << paths.size() << endl;
}
