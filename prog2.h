#ifndef PROG2_H
#define PROG2_H

#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Node {
  private:
   int data;
   int parent;
   int rank;
 public:
    Node() {
      	data = 0;
      	parent = 0;
      	rank = 0;
    }

    Node(int d) {
      	data = d;
        parent = d;
        rank = 0;
    }

    int getData() const { return data; }
    void setData(int d) { data = d; }
    
    int getParent() const { return parent; }
    void setParent(int p) { parent = p; }
    
    int getRank() const { return rank; }
    void setRank(int r) { rank = r; }
};

class Edge {
  private:
    int a; //Node A
    int b; //Node B
    int w; //Weight
    bool i; //Inserted?

  public:
    Edge(int p, int q, int weight) {
        a = p;
        b = q;
        w = weight;
        i = 0;
    }

    int getA() const { return a; }
    void setA(int node) { a = node; }

    int getB() const { return b; }
    void setB(int node) { b = node; }

    int getW() const { return w; }
    void setW(int weight) { w = weight; }

    bool getI() const { return i; }
    void setI(int inserted) { i = inserted; }
};

class UFDS {
  private:
    Node **NodeArray;
    Edge **EdgeArray;
    int nodes;
    int edges;

  public:
    UFDS(int n, int m) { //n = nodes, m = edges
        nodes = n;
        edges = m;
        NodeArray = new Node*[nodes];
        for (int i=1; i<nodes+1; i++) {
            NodeArray[i] = new Node(i);
        }
        EdgeArray = new Edge*[edges];
        for (int i=0; i<edges; i++) {
            EdgeArray[i] = NULL;
        }
    }

    bool newEdge(int a, int b, int w) {
        //Check if EdgeArray is full
        if (EdgeArray[edges-1]!=NULL) {
        	cout << "Error: EdgeArray full; cannot add edge between " << a <<
        	 " and " << b << endl;
        	 return 0;
        }
        //Loop to find insertion index
        for (int i=0; i<edges; i++) {
        	if (EdgeArray[i] == NULL) {
        		EdgeArray[i] = new Edge(a,b,w);
        		return 1;
        	}
        	else if (
        		(EdgeArray[i]->getW()==w && EdgeArray[i]->getA()==a && EdgeArray[i]->getB()>b) ||
        		(EdgeArray[i]->getW()==w && EdgeArray[i]->getA()>a) || 
        		(EdgeArray[i]->getW()>w)) {
        		//Shift all nodes after index i right; beginning at penultimate node
        		for (int j=edges-2; j>=i; j--) {
        			//Would only run on first loop
        			if (EdgeArray[j]!=NULL && EdgeArray[j+1]==NULL) {
        				EdgeArray[j+1] = new Edge(EdgeArray[j]->getA(),EdgeArray[j]->getB(),
        					EdgeArray[j]->getW());
        			}
        			//Shift node right one index
        			else if (EdgeArray[j]!=NULL && EdgeArray[j+1]!=NULL) {
        				EdgeArray[j+1]->setA(EdgeArray[j]->getA());
        				EdgeArray[j+1]->setB(EdgeArray[j]->getB());
        				EdgeArray[j+1]->setW(EdgeArray[j]->getW());
        			}
        		}
        		//After shifting is done, insert new edge
        		EdgeArray[i]->setA(a);
        		EdgeArray[i]->setB(b);
        		EdgeArray[i]->setW(w);
        		return 1;
        	}
        }
    	cout << "Error could not insert edge between " << a << " and " << b << endl;
    	return 0;
    }

    int find(int x) {
        if (NodeArray[x]->getParent() != NodeArray[NodeArray[x]->getParent()]->getParent()) {
            NodeArray[x]->setParent(find(NodeArray[x]->getParent()));
        }
        //cout << "find(" << x << ") = " << NodeArray[x]->getParent() << endl;
        return NodeArray[x]->getParent();
    }

    bool unify(int a, int b) {
  	    if (find(a) == find(b)) {
            cout << "Edge (" << a << "," << b << ") creates cycle" << endl;
            return 0;
        }
        else if (NodeArray[a]->getRank() == NodeArray[b]->getRank()) {
            NodeArray[a]->setRank(NodeArray[a]->getRank() + 1);
            NodeArray[b]->setParent(a);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        else if (NodeArray[a]->getRank() > NodeArray[b]->getRank()) {
            NodeArray[a]->setRank(NodeArray[a]->getRank() + NodeArray[b]->getRank());
            NodeArray[b]->setParent(a);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        else if (NodeArray[a]->getRank() < NodeArray[b]->getRank()) {
            NodeArray[b]->setRank(NodeArray[b]->getRank() + NodeArray[a]->getRank());
            NodeArray[a]->setParent(b);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        cout << "Error: Unable to perform union." << endl;
        return 0;
    }

    void Kruskal() {
        for (int i=0; i<edges; i++) {
        	if (unify(EdgeArray[i]->getA(), EdgeArray[i]->getB()) == 1) {
                EdgeArray[i]->setI(1);
            }
        }
    }

    void print() const {
        int totalweight=0, count=0;
        //Check if it is a MST
        for (int i=0; i<edges; i++) {
            if (EdgeArray[i]->getI()==1) {
                count++;
            }
        }
        if (count != (nodes-1)) {
            cout << "Error: MST not found." << endl;
            exit(0);
        }

        //If it is a MST, print edges
        for (int i=0; i<edges; i++) {
            if (EdgeArray[i]->getI()==1) {
                cout << EdgeArray[i]->getA() << " " << EdgeArray[i]->getB() << endl;;
                totalweight += EdgeArray[i]->getW();
            }
        }
        //Print weight of MST
        if (totalweight == 0) {
            cout << "ERROR: MST not found." << endl;
        }
        else
            cout << totalweight << endl;
    }
};

#endif