#include "globals.h"

int main() 
{
	graph g(16);
	g.connect();
	g.greedyColoring();

	system("pause");
	return 0;
}