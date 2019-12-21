#include "ReadFromFile.h"
#include <iostream>
#include <fstream>
using namespace std;

ReadFromFile::ReadFromFile() {

}

ReadFromFile::ReadFromFile(string name)
{
	ifstream inputFile;
	
	inputFile.open(name);
	if (!inputFile)		//alternative to file.fail()
	{
		cout << "Error in finding file" << endl;
		system("pause");
		exit(-1);
	}
	inputFile >> sizeOfBoard;
	vectorBoard.resize(sizeOfBoard);
	for (int i = 0; i < sizeOfBoard; ++i)
		vectorBoard[i].resize(sizeOfBoard);
	if (!inputFile.eof())	// if not End Of File 
	{
		for (int i = 0; i < sizeOfBoard; ++i)
			for (int j = 0; j < sizeOfBoard; ++j) {
				if (inputFile.eof()) {
					cout << "Error in reading board" << endl;
					system("pause");
					exit(-1);
				}
				char x;
				inputFile >> x;
				
					if (x == '-')
						vectorBoard[i][j] = -1;
					else 
						vectorBoard[i][j] =x-'0';
				
			}
	}
	else
	{
		cout << "Error in reading board" << endl;
		system("pause");
		exit(-1);
	}
}


