#pragma once
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class ReadFromFile
{
public:
	int sizeOfBoard;
	vector<vector<int>>vectorBoard;
	ReadFromFile();
	ReadFromFile(string name);
};

