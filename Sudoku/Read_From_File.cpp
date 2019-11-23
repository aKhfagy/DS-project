#include "Read_From_File.h"
#include <iostream>
#include <fstream>
using namespace std;
Read_From_File::Read_From_File()
{
	ifstream inputFile;
	inputFile.open("Text.txt");
	if (!inputFile)
		cout << "Error";
	inputFile >> sizeOfBoard;
	arrayBoard = new int*[sizeOfBoard];
	for (int i = 0; i < sizeOfBoard; i++)
	{
		arrayBoard[i] = new int[sizeOfBoard];
	}
	char x;
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{

			inputFile >> x;
			if (x == '|')j--;
			else if (x == ' ')j++;
			else arrayBoard[i][j] = x - '0';
		}
	}
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
			cout << arrayBoard[i][j];
		}
		cout << endl;
	}
}
