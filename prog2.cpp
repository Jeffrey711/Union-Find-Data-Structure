#include <stdio.h>
#include <string>
#include "prog2.h"
using namespace std;

int main(int argc, char *argv[]) {
	int nodes=0, edges=0, count=0;
	cin >> nodes;
	cin >> edges;

	UFDS *MST = new UFDS(nodes, edges);

	int a=0, b=0, w=0;

	while (count < edges) {
		cin >> a;
		cin >> b;
		cin >> w;
		if (a>b)
			MST->newEdge(b,a,w);
		else
			MST->newEdge(a,b,w);
		count++;
	}
	MST->Kruskal();
	MST->print();
	free(MST);
}