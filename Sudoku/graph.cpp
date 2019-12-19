#include "graph.h"

using namespace std;
 
 
graph::graph(int v)
{
	V = v;
	adj.resize(v);
	color = new int[v];
	available = new bool[v];
}
 
void graph::addEdge(int v1, int v2) {
 
	adj[v1].push_back(v2);
	adj[v2].push_back(v1);
 
}
 
void graph::connect() 
{
 
	int sizeOfBoard= int(sqrt(V));

	//connect every row
	int s = sizeOfBoard;
	for (int i = 0; i < V; i++) {
		int inc = 1;
		for (int j = i + inc; j < s; j++) {
			addEdge(i, j);
			inc++;
		}
		if ((i + 1) % sizeOfBoard == 0)
			s += sizeOfBoard;
		else if (s > V)
			break;
	}
	//connect every column

	for (int i = 0; i < V; i++) {
		int inc = sizeOfBoard;
		for (int ctr = 0; ctr < V; ctr++)
		{
			int j = i + inc;
			if (j >= V) break;
			else {
				addEdge(i, j);
				inc += sizeOfBoard;
			}

		}
	}

	//connect sub boxes
	int n = sizeOfBoard;
	int r = sqrt(n);
	for (int i = 0, ctr1 = 0; i < V, ctr1 < r; i = i + pow(r, r), ctr1++)
		for (int j = i, ctr2 = 0; j < V, ctr2 < r; j = j + r, ctr2++) {
			subbox(j, n);
			//cout << j << endl;
		}
 
	//int size = int(sqrt(V));

	//int sectorSize = int(sqrt(size));

	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j) {
	//		for (int row = i + 1; row < size; ++row)
	//			addEdge(i * size + j, row * size + j);
 //
	//		for (int col = j + 1; col < size; ++col)
	//			addEdge(i * size + j, i * size + col);
	//	}
	//}
 //
	//for (int i = 0; i < size; i += sectorSize)
	//	for (int j = 0; j < size; j += sectorSize)
	//		for (int row = i; row - i < sectorSize; ++row)
	//			for (int col = j; col - j < sectorSize; ++col)
	//				for (int inRow = i; inRow - i < sectorSize; ++inRow)
	//					for (int inCol = j; inCol - j < sectorSize; ++inCol)
	//						if (row == inRow and col == inCol)
	//							continue;
	//						else
	//							addEdge(row * size + col, inRow * size + inCol);
 //
 //
 
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
				//	cout << j << "  " << k << endl;
			}
		}
	}
}
void graph::greedyColoring()
{
	ReadFromFile obj;
 
	connect();

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
	//delete[] adj;
	delete[]color;
	delete[]available;
}

/*

void Graph::connect(int sizeOfBoard)  //size like 4 or 9
{
	int v = sizeOfBoard * sizeOfBoard;
	//connect every row
	int s = sizeOfBoard;
	for (int i = 0; i < v; i++) {
		int inc = 1;
		for (int j = i + inc; j < s; j++) {
			addEdge(i, j);
			inc++;
		}
		if ((i + 1) % sizeOfBoard == 0)
			s += sizeOfBoard;
		else if (s > v)
			break;
	}
	//connect every column

	for (int i = 0; i < v; i++) {
		int inc = sizeOfBoard;
		for (int ctr = 0; ctr < v; ctr++)
		{
			int j = i + inc;
			if (j >= v) break;
			else {
				addEdge(i, j);
				inc += sizeOfBoard;
			}

		}
	}

	//connect sub boxes
	int n = sizeOfBoard;
	int r = sqrt(n);
	for (int i = 0,  ctr1=0  ; i < v, ctr1<r ; i = i + pow(r, r),ctr1++ )
		for (int j = i, ctr2=0; j < v,ctr2<r ;j=j+ r , ctr2++) {
			subbox(j,n,v);
			//cout << j << endl;
		}
	}
void Graph::subbox(int j,int n) // j is the leading element in every sub box,
//n is the the size of sudoku (ex: 9), v is the number of vertice
{
	int A = j;
	int r = sqrt(n);
	int ctr1 = 0;
	for (j ;    j < V;    j++, ctr1++) {
		int ctr2 = 0;
		if (ctr1 == r) break;
		for (int k = A + n;     k<v;   k = k + (n - r), ctr2++) { //k=k+7
			int ctr3 = 0;
			if (ctr2 == r - 1) break;
			for (k;    k < V;   ctr3++, k++) {
				if (ctr3 == r) break;
				addEdge(j,k);
			//	cout << j << "  " << k << endl;
			}
		}
	}

}

*/