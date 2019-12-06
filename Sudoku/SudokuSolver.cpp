#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
	size = 9;
	isDiagonal = false;
	grid = new int* [size];
	for (int i = 0; i < size; ++i)
		grid[i] = new int[size];
}

SudokuSolver::SudokuSolver(int** temp, int toAssignSize = 9) {
	size = toAssignSize;
	isDiagonal = false;
	grid = new int* [size];
	for (int i = 0; i < size; ++i)
		grid[i] = new int[size];
	grid = temp;
}

SudokuSolver::SudokuSolver(int** temp, int toAssignSize = 0, bool flag = false) {
	size = toAssignSize;
	isDiagonal = flag;
	grid = new int* [size];
	for (int i = 0; i < size; ++i)
		grid[i] = new int[size];
	grid = temp;
}

cell SudokuSolver::findNextCellToFill() {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (grid[i][j] == 0)
				return std::make_pair(i, j);
	return std::make_pair(NIL, NIL);
}

bool SudokuSolver::checkDiagonals() {
	bool* vis = new bool[size + 1];

	// TODO: fix this code

	for (int i = 0; i <= size; ++i)
		vis[i] = false;

	for (int i = 0; i < size; ++i) {
		if (vis[grid[i][i]] and grid[i][i] != 0)
			return false;
		grid[i][i] = true;
	}

	for (int i = 0; i <= size; ++i)
		vis[i] = false;

	for (int i = 0; i < size; ++i) {
		if (vis[grid[i][9 - i - 1]] and grid[i][9 - i - 1] != 0)
			return false;
		grid[i][9 - i - 1] = true;
	}

	delete[] vis;

	return true;
}

bool SudokuSolver::isValid(int x, int y) {
	int sectorSize = int(sqrt(size));

	bool* vis = new bool[size + 1];

	for (int i = 0; i <= size; ++i)
		vis[i] = false;

	for (int i = 0; i < size; ++i) {
		if (vis[grid[i][y]] and grid[i][y] != 0)
			return false;
		vis[grid[i][y]] = true;
	}

	for (int i = 0; i <= size; ++i)
		vis[i] = false;

	for (int i = 0; i < size; ++i) {
		if (vis[grid[x][i]] and grid[x][i] != 0)
			return false;
		vis[grid[x][i]] = true;
	}

	for (int i = 0; i < size; i += sectorSize) {
		for (int j = 0; j < size; j += sectorSize) {
			for (int i = 0; i <= size; ++i)
				vis[i] = false;
			for (int row = i; row - i != sectorSize; ++row) {
				for (int col = j; col - j != sectorSize; ++col) {
					if (vis[grid[row][col]] and grid[row][col] != 0)
						return false;
					vis[grid[row][col]] = true;
				}
			}
		}
	}

	if (isDiagonal and !checkDiagonals())
		return false;

	delete[] vis;

	return true;
}

void SudokuSolver::display() {
	int sectorSize = int(sqrt(size));

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (j == 0)
				std::cout << ' ' << '|' << ' ';
			std::cout << grid[i][j] << ' ';
			if ((j + 1) % sectorSize == 0 and j != size - 1)
				std::cout << '|' << ' ';
			else if (j == size - 1)
				std::cout << '|';
		}
		if ((i + 1) % sectorSize == 0) 
			std::cout << "\n";
		std::cout << '\n';
	}
}

bool SudokuSolver::solveSudoku() {
	cell here = findNextCellToFill();
	int x = here.first, y = here.second;
	if (x == NIL) 
		return true;
	for (int num = 1; num <= size; ++num) {
		grid[x][y] = num;
		if (isValid(x, y)) {
			if (solveSudoku())
				return true;
		}
		grid[x][y] = 0;
	}
	return false;
}

void SudokuSolver::solve() {
	if (solveSudoku())
		display();
	else
		puts("There is no solution");
}

SudokuSolver::~SudokuSolver() {
	for (int i = 0; i < size; ++i)
		delete[] grid[i];
	delete[] grid;
}
