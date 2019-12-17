#include "ReadFromFile.h"
#include <iostream>
#include <fstream>
using namespace std;
ReadFromFile::ReadFromFile()
{
	ifstream inputFile;
	inputFile.open("SudokuData.txt");
	if (!inputFile)		//alternative to file.fail()
	{
		cout << "Error in finding file" << endl;
		system("pause");
		exit(-1);
	}
	inputFile >> sizeOfBoard;
	if (!inputFile.eof())	// if not End Of File 
	{
		arrayBoard = new int[sizeOfBoard*sizeOfBoard];
		char x;
		for (int i = 0; i < sizeOfBoard*sizeOfBoard; i++)
		{

			inputFile >> x;
			if (x == '|') i--;
			else if (x == '-') arrayBoard[i] = -1; //empty space = -1 in the array
			else arrayBoard[i] = x - '0';
		}
	}
	else
	{
		cout << "Error in reading board" << endl;
		system("pause");
		exit(-1);
	}
	/*
	//output
	for (int i = 0; i < sizeOfBoard*sizeOfBoard; i++)
	{
		if (i != 0 && i % sizeOfBoard == 0) cout << endl;
		cout << arrayBoard[i] << " ";
	}
	*/
}

ReadFromFile::~ReadFromFile()
{
	delete[] arrayBoard;
}
