#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
	size = 9;
	grid.resize(size);
	for (auto row : grid)
		row.resize(size);
}

SudokuSolver::SudokuSolver(board temp, int toAssignSize = 9) {
	size = toAssignSize;
	grid = temp;
}

cell SudokuSolver::findNextCellToFill() {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (grid[i][j] == 0)
				return cell(i, j);
	return cell(NIL, NIL);
}

bool SudokuSolver::isValid(int x, int y) {
	int sectorSize = int(sqrt(size));

	bool* vis = new bool[size + 1LL];

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

	delete[] vis;

	return true;
}

void SudokuSolver::saveToFile(std::ofstream& outFile) {
	int sectorSize = int(sqrt(size));
	outFile << size << '\n';
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (j == 0)
				outFile << ' ' ;
			outFile << grid[i][j] << ' ';

			if ((j + 1) % sectorSize == 0 and j != size - 1)
				outFile <<  ' ';
		}
		if ((i + 1) % sectorSize == 0)
			outFile << "\n";
		outFile << '\n';
	}
	outFile << "\n";
	outFile << "________________________________________________________\n\n\n";
}

void SudokuSolver::outputAll(bool& flag, std::ofstream& file) {
	cell here = findNextCellToFill();
	int x = here.first, y = here.second;
	if (x == NIL) {
		flag = true;
		saveToFile(file);
		return;
	}
	for (int num = 1; num <= size; ++num) {
		grid[x][y] = num;
		if (isValid(x, y))
			outputAll(flag, file);
		grid[x][y] = 0;
	}
	flag |= false;
}

bool SudokuSolver::giveOutAll() {
	bool flag;
	std::ofstream outFile("outputAll.txt");
	outputAll(flag, outFile);
	outFile.close();
	return flag;
}

bool SudokuSolver::solveSudoku() {
	cell here = findNextCellToFill();
	int x = here.first, y = here.second;
	if (x == NIL)
		return true;
	for (int num = 1; num <= size; ++num) {
		grid[x][y] = num;
		if (isValid(x, y))
			if (solveSudoku())
				return true;
		grid[x][y] = 0;
	}
	return false;
}

void SudokuSolver::failed() {
	std::ofstream outFile("outputSingle.txt");
	outFile << "There is no solution\n";
	outFile.close();
}

void SudokuSolver::saveSingle() {
	std::ofstream outFile("outputSingle.txt");
	saveToFile(outFile);
	outFile.close();
}

void SudokuSolver::getAll() {
	if (not giveOutAll())
		failed();
}

void SudokuSolver::solve() {
	if (solveSudoku())
		saveSingle();
	else
		failed();
}
