#include "graph.h"
#include<iterator>
#include "ReadFromFile.h"
#include<iostream>
#include <fstream>
#include<cmath>
using namespace std;


graph::graph(int v)
{
	adj = new vector<int>[v];
	color = new int[v];
	available = new bool[v];
}

void graph::addEdge(int v1, int v2) {

	adj[v1].push_back(v2);
	adj[v2].push_back(v1);

}

void graph::connect(int sizeOfBoard)
{

	int sectorSize = int(sqrt(sizeOfBoard));


	for (int i = 0; i < sizeOfBoard; ++i) {
		for (int j = 0; j < sizeOfBoard; ++j) {
			for (int row = i + 1; row < sizeOfBoard; ++row)
				addEdge(i * sizeOfBoard + j, row * sizeOfBoard + j);

			for (int col = j + 1; col < sizeOfBoard; ++col)
				addEdge(i * sizeOfBoard + j, i * sizeOfBoard + col);
		}
	}

	for (int i = 0; i < sizeOfBoard; i += sectorSize)
		for (int j = 0; j < sizeOfBoard; j += sectorSize)
			for (int row = i; row - i != sectorSize; ++row)
				for (int col = j; col - j != sectorSize; ++col)
					for (int inRow = i; inRow - i != sectorSize; ++inRow)
						for (int inCol = j; inCol - j != sectorSize; ++inCol)
							if (row == inRow and col == inCol)
								continue;
							else
								addEdge(row * sizeOfBoard + col, inRow * sizeOfBoard + inCol);



}
void graph::greedyColoring(int v)
{
	ReadFromFile obj;

	for (int u = 0; u < v; u++)
	{
		color[u] = obj.arrayBoard[u];
	}
	//output 
	int boardSize = int(sqrt(v));
	for (int i = 0; i < v; i++)
	{
		if (i != 0 && i % boardSize == 0) cout << endl;
		if (color[i] == -1) cout << color[i] << " ";
		else cout << color[i] << "  ";
	}
	cout << endl; cout << endl; cout << endl;

	for (int cr = 0; cr < v; cr++)
	{
		if (color[cr] != -1) available[cr] = true;
		else available[cr] = false;
	}
	/*
	for (int j = 0; j < v; j++)
	{
		cout << available[j] << " " << color[j] << endl;
	}
	cout << endl << "gawa el loop el kbera u "<<endl;
	*/
	for (int u = 0; u < v; u++)
	{

		//puts("==========================================");
		//// Process all adjacent vertices and flag their colors 
		//// as unavailable 

		vector<int>::iterator i;
		//cout << u << "--->";
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (color[*i] != -1)
			{
				//cout << *i<<" "<< color[*i]<<endl;
				available[color[*i]] = true;
			}

		}

		int cntr = 0;
		int cr;
		for (cr = 1; cr < v; cr++)
		{
			if (available[cr] == false)
			{
				break;
			}
		}
		if (color[u] == -1) color[u] = cr;

		/*
		cout << color[u]<<" "<< available[u] << endl;
		for (int i = 0; i < v; i++)
		{
			if (i != 0 && i % boardSize == 0) cout << endl;
			cout << color[i] << " ";
		}
		cout << endl; cout << endl; cout << endl;
		*/
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (color[*i] != -1)
			{
				available[color[*i]] = false;
			}
		}
	}
	bool canGreedySolve = true;
	for (int u = 0; u < v; u++)
	{
		if (color[u] > boardSize)
		{
			canGreedySolve = false;
			break;
		}
	}
	if (!canGreedySolve)
		/// connect with another algo 

	else
	{
		//output
		int sectorSize = int(sqrt(v));
		for (int u = 0; u < v; u++) {
			//cout << "Vertex " << u << " --->  Color " << color[u] << endl;
			cout << color[u] << "  ";
			if ((u + 1) % sectorSize == 0)  cout << endl;
		}
	}
}
graph::~graph()
{
	delete[] adj;
	delete[]color;
	delete[]available;
}
