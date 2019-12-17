#include<iostream>
#include<string> 
#include"graph.h"
#include <stdlib.h> //rand
using namespace std;
bool colAndRow(int boardSize, int**board, int row, int col, int num);
int inBox(int boardSize, int**board, int row, int col, int boxRow, int boxCol);
void disp(int **board, int n);
void easy();
void hard();

int main()
{
	string choice;
	cin >> choice;
	if (choice == "easy") //easy
	{
		easy();
	}
	else 
	{
		hard();
	}
	system("pause");
	return 0;
}
bool colAndRow(int boardSize, int**board, int row, int col, int num)
{
	//col
	for (int i = 0; i < boardSize; i++)
	{
		if (board[i][col] == num) return false;
	}
	//row
	for (int i = 0; i < boardSize; i++)
	{
		if (board[row][i] == num) return false;
	}
	return true;
}

int inBox(int boardSize, int**board, int row, int col, int boxRow, int boxCol)
{
	int num = 1 + (rand() % boardSize);
	if (!colAndRow(boardSize, board, row, col, num))
		return -1;
	else
	{
		//cout << ibox << " " << ibox + sqrt(n)-1 << endl;
		//box
		for (int i = boxRow; i <= boxRow + sqrt(boardSize) - 1; i++)
		{
			for (int j = boxCol; j <= boxCol + sqrt(boardSize) - 1; j++)
			{
				if (board[i][j] == num) return -1;
			}
		}
		return num;
	}
}
void disp(int **board, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl; cout << endl;
}

void easy()
{
	int boardSize = 4;
	int **board = new int*[boardSize];
	for (int i = 0; i < boardSize; i++)
		board[i] = new int[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i][j] = -1;
		}
	}
	if (boardSize == 4) //easy
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (i >= 0 && i <= sqrt(boardSize) - 1)
				{
					if (j >= 0 && j <= sqrt(boardSize) - 1)
						board[i][j] = inBox(boardSize, board, i, j, 0, 0);
					else if (j >= sqrt(boardSize) && j <= sqrt(boardSize) + 2)
						board[i][j] = inBox(boardSize, board, i, j, 0, 2);

				}
				else if (i >= sqrt(boardSize) && i <= sqrt(boardSize) + 2)
				{
					if (j >= 0 && j <= sqrt(boardSize) - 1)
						board[i][j] = inBox(boardSize, board, i, j, 2, 0);
					else if (j >= sqrt(boardSize) && j <= sqrt(boardSize) + 2)
						board[i][j] = inBox(boardSize, board, i, j, 2, 2);

				}
			}
		}

	}
	disp(board, boardSize);
}

void hard()
{
	int boardSize = 9;
	int **board = new int*[boardSize];
	for (int i = 0; i < boardSize; i++)
		board[i] = new int[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i][j] = -1;
		}
	}

	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (i >= 0 && i <= sqrt(boardSize) - 1)
			{
				if (j >= 0 && j <= sqrt(boardSize) - 1)
					board[i][j] = inBox(boardSize, board, i, j, 0, 0);
				else if (j >= sqrt(boardSize) && j <= sqrt(boardSize) + 2)
					board[i][j] = inBox(boardSize, board, i, j, 0, 3);
				else
					board[i][j] = inBox(boardSize, board, i, j, 0, 6);

			}
			else if (i >= sqrt(boardSize) && i <= sqrt(boardSize) + 2)
			{
				if (j >= 0 && j <= sqrt(boardSize) - 1)
					board[i][j] = inBox(boardSize, board, i, j, 3, 0);
				else if (j >= sqrt(boardSize) && j <= sqrt(boardSize) + 2)
					board[i][j] = inBox(boardSize, board, i, j, 3, 3);
				else
					board[i][j] = inBox(boardSize, board, i, j, 3, 6);
			}
			else
			{
				if (j >= 0 && j <= sqrt(boardSize) - 1)
					board[i][j] = inBox(boardSize, board, i, j, 6, 0);
				else if (j >= sqrt(boardSize) && j <= sqrt(boardSize) + 2)
					board[i][j] = inBox(boardSize, board, i, j, 6, 3);
				else
					board[i][j] = inBox(boardSize, board, i, j, 6, 6);
			}
		}
	}

	disp(board, boardSize);

}