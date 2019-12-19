#include "graph.h"

using namespace std;
 
 
graph::graph(int v)
{
	V = v;
	adj = new vector<int>[v];
	color = new int[v];
	available = new bool[v];
}
 
void graph::addEdge(int v1, int v2) {
 
	adj[v1].push_back(v2);
	adj[v2].push_back(v1);
 
}
 
void graph::connect() 
{
 
	int size = int(sqrt(V));

	int sectorSize = int(sqrt(size));
 
 
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int row = i + 1; row < size; ++row)
				addEdge(i * size + j, row * size + j);
 
			for (int col = j + 1; col < size; ++col)
				addEdge(i * size + j, i * size + col);
		}
	}
 
	for (int i = 0; i < size; i += sectorSize)
		for (int j = 0; j < size; j += sectorSize)
			for (int row = i; row - i < sectorSize; ++row)
				for (int col = j; col - j < sectorSize; ++col)
					for (int inRow = i; inRow - i < sectorSize; ++inRow)
						for (int inCol = j; inCol - j < sectorSize; ++inCol)
							if (row == inRow and col == inCol)
								continue;
							else
								addEdge(row * size + col, inRow * size + inCol);
 
 
 
}
void graph::greedyColoring()
{
	ReadFromFile obj;
 
	
	int boardSize = int(sqrt(V));

	for (int i = 0, idx = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
			color[idx++] = obj.vectorBoard[i][j];
	}
	//output 
	for (int i = 0; i < V; i++)
	{
		if (i != 0 && i % boardSize == 0) cout << endl;
		if(color[i]==-1) cout << color[i] << " ";
		else cout << color[i] << "  ";
	}
	cout << endl; cout << endl; cout << endl;
 
	for (int cr = 0; cr < V; cr++)
	{
		if(color[cr]!=-1) available[cr] = true;
		else available[cr] = false;
	}
	for (int u = 0; u < V; u++)
	{
		vector<int>::iterator i;
		//cout << u << "--->";
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (color[*i] != -1 )
			{
			 	//cout << *i<<" "<< color[*i]<<endl;
				available[color[*i]] = true;
			}
 
		}
 
		int cntr = 0;
		int cr;
		for (cr = 1; cr < V; cr++)
		{
			if (available[cr] == false)
			{
				break;
			}
		}
		if(color[u]==-1) color[u] = cr;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (color[*i] != -1)
			{
				available[color[*i]] = false;
			}
		}
	}
	bool canGreedySolve = true;
	for (int u = 0; u < V; u++) 
	{
		if (color[u] > boardSize)
		{
			canGreedySolve = false;
			break;
		}
	}

	if (canGreedySolve)
	{
		//output
		for (int u = 0; u < V; u++) {
			//cout << "Vertex " << u << " --->  Color " << color[u] << endl;
			cout << color[u] << "  ";
			if ((u + 1) % boardSize == 0)  cout << endl;
		}
	}
	else
	{
	//other algo	
		cout << "Greedy Cant Solve "<<endl;
		for (int i = 0; i < obj.vectorBoard.size(); ++i) {
			for (int j = 0; j < obj.vectorBoard[i].size(); ++j)
				if (obj.vectorBoard[i][j] == -1)
					obj.vectorBoard[i][j] = 0;
		}
		SudokuSolver(obj.vectorBoard, boardSize).solve();
	}
	
}
graph::~graph()
{
	delete[] adj;
	delete[]color;
	delete[]available;
}