#include "graph.h"

using namespace std;


graph::graph(ReadFromFile read)
{
	obj = read;
	V = obj.sizeOfBoard * obj.sizeOfBoard;
	adj.resize(V);
	color = new int[V];
	available = new bool[V];

}

void graph::addEdge(int v1, int v2) {

	adj[v1].push_back(v2);
	adj[v2].push_back(v1);

}

void graph::getAll() {
	for (int i = 0; i < obj.vectorBoard.size(); ++i) {
		for (int j = 0; j < obj.vectorBoard[i].size(); ++j)
			if (obj.vectorBoard[i][j] == -1)
				obj.vectorBoard[i][j] = 0;
	}
	SudokuSolver(obj.vectorBoard, int(sqrt(V))).getAll();
	puts("Output was saved in outputAll.txt");
}

void graph::connect()
{
	int size = int(sqrt(V));
	int sizeOfBoard = int(sqrt(V));

	//connect every row
	int s = size;
	for (int i = 0; i < V; i++) {
		int inc = 1;
		for (int j = i + inc; j < s; j++) {
			addEdge(i, j);
			//cout << i << " "<< j << endl;
			inc++;
		}
		if ((i + 1) % size == 0)
			s += size;
		else if (s > V)
			break;
	}
	//connect every column

	for (int i = 0; i < V; i++) {
		int inc = size;
		for (int ctr = 0; ctr < V; ctr++)
		{
			int j = i + inc;
			if (j >= V) break;
			else {
				addEdge(i, j);
				//cout << i <<" "<< j << endl;
				inc += size;
			}

		}
	}

	//connect sub boxes
	int n = size;
	int r = sqrt(n);
	for (int i = 0, ctr1 = 0; i < V && ctr1 < r; i = i + pow(r, 3), ctr1++) {
		for (int j = i, ctr2 = 0; j < V && ctr2 < r; j = j + r, ctr2++) {
			subbox(j, n);
			//cout << j << endl;
		}
	}

}

void graph::subbox(int j, int n) // j is the leading element in every sub box,
//n is the the size of sudoku (ex: 9), v is the number of vertice
{
	int A = j;
	int r = sqrt(n);
	int ctr1 = 0;
	for (j; j < V; j++, ctr1++) {
		int ctr2 = 0;
		if (ctr1 == r) break;
		for (int k = A + n; k < V; k = k + (n - r), ctr2++) {
			int ctr3 = 0;
			if (ctr2 == r - 1) break;
			for (k; k < V; ctr3++, k++) {
				if (ctr3 == r) break;
				addEdge(j, k);
				//cout << j << "  " << k << endl;
			}
		}
	}
}

void graph::greedyColoring()
{
	connect();
	int boardSize = int(sqrt(V));
	int count = 0;
	for (int i = 0, idx = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			color[count] = obj.vectorBoard[i][j];
			count++;
		}
	}/*
	for (int cr = 0; cr < V; cr++)
	{
		if (color[cr] != -1) available[cr] = true;
		else available[cr] = false;
	}*/
	//output 

	//for (int i = 0; i < V; i++)
	//{
	//	if (i != 0 && i % boardSize == 0) cout << endl;
	//	if(color[i]==-1) cout << color[i] << " ";            //check the read file
	//	else cout << color[i] << "  ";
	//}
	//cout << endl; cout << endl; cout << endl;

//----------------------------


	for (int u = 0; u < V; u++)
	{
		vector<int>::iterator i;

		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (color[*i] != -1)
			{
				//cout << *i<<" "<< color[*i]<<endl;
				available[color[*i]] = true;                 //to make the number (color) taken ie. not available
			}                                               //to give new colors to the uncolored (empty)

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
		if (color[u] == -1) color[u] = cr;                  //if the cell is empty give it the free color

		       //for optimization (less no. of colors)
		
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
		ofstream outFile("outputGreedy.txt");

		//output
		for (int u = 0; u < V; u++) {
			//cout << "Vertex " << u << " --->  Color " << color[u] << endl;
			outFile << color[u] << "  ";
			if ((u + 1) % boardSize == 0)  outFile << endl;
		}

		outFile.close();

		puts("Output was saved in outputGreedy.txt");
	}
	else
	{
		//other algo	
		for (int i = 0; i < obj.vectorBoard.size(); ++i) {
			for (int j = 0; j < obj.vectorBoard[i].size(); ++j)
				if (obj.vectorBoard[i][j] == -1)
					obj.vectorBoard[i][j] = 0;
		}
		SudokuSolver(obj.vectorBoard, boardSize).solve();
		puts("Output was saved in outputSingle.txt");
	}

}
graph::~graph()
{
	delete[]color;
	//delete[]available;
}
