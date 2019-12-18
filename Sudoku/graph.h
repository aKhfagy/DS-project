#pragma once
#include<vector>
#include<iostream>
#include<iterator>
using namespace std;

class graph
{
	int V;
	vector<int> *adj;
	int * color;
	bool *available;
	//int arrayboard[4][4];

public:
	graph(int v);
	void addEdge(int v1, int v2);
	void greedyColoring(int v);
	void connect(int n);
	~graph();
};

