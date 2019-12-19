#pragma once
#include<iterator>
#include "ReadFromFile.h"
#include<iostream>
#include <fstream>
#include "SudokuSolver.h"
#include<cmath>
#include <vector>
using namespace std;

class graph
{
	int V;
	ReadFromFile obj;
	vector<vector<int>> adj;
	bool* available;
	void addEdge(int v1, int v2);
	void subbox(int,int);
	void connect();
public:
	int* color;
	graph(ReadFromFile read);
	void getAll();
	void greedyColoring();
	~graph();
};