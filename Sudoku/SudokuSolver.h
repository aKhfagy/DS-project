#pragma once
#include <utility>
#include <fstream>
#include <vector>
constexpr auto NIL = -1;
typedef std::vector <std::vector <int>> board;
typedef std::pair<int, int> cell;

class SudokuSolver
{
	board grid;
	int size;
	bool solveSudoku();
	cell findNextCellToFill();
	bool giveOutAll();
	void saveToFile(std::ofstream&);
	void outputAll(bool&, std::ofstream&);
	bool isValid(int x, int y);
	void failed();
	void saveSingle();
public:
	SudokuSolver();
	SudokuSolver(board, int);
	void getAll();
	void solve();
};

