#pragma once
#include <iostream>
#include <utility>
constexpr auto NIL = -1;
typedef std::pair<int, int> cell;

class SudokuSolver
{
	int** grid;
	int size;
	bool isDiagonal;
	bool solveSudoku();
	cell findNextCellToFill();
	bool checkDiagonals();
	bool isValid(int x, int y);
	void display();
public:
	SudokuSolver();
	SudokuSolver(int**, int);
	SudokuSolver(int**, int, bool);
	void solve();
	~SudokuSolver();
};

