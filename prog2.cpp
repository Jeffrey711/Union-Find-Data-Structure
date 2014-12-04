#include <stdio.h>
#include <string>
#include "prog2.h"
using namespace std;

int main(int argc, char *argv[]) {
	int nodes=0, edges=0, count=0;
	
	//Read in number of nodes and edges
	cin >> nodes;
	cin >> edges;

	//Allocate memory for Union-Find Data Structure
	UFDS *MST = new UFDS(nodes, edges);

	int a=0, b=0, w=0;

	while (count < edges) {
		//Read in edge nodes and weight
		cin >> a;
		cin >> b;
		cin >> w;

		//Make sure node A < node B
		if (a>b)
			MST->newEdge(b,a,w);
		else
			MST->newEdge(a,b,w);
		count++;
	}
	MST->Kruskal(); //Perform sort and union
	MST->print(); //Prints out inserted edges
	free(MST); //Deallocate memory
}