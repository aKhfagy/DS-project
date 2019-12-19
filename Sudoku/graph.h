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
	vector<vector<int>> adj;
	int* color;
	bool* available;
	//int arrayboard[4][4];

public:
	graph(int v);
	void addEdge(int v1, int v2);
	void greedyColoring();
	void connect();
	void subbox(int,int);
	~graph();
};