#ifndef PROG2_H
#define PROG2_H

#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//
class Node {
  private:
   int data;
   int parent;
   int rank;
 public:
    //Default constructor
    Node() {
      	data = 0;
      	parent = 0;
      	rank = 0;
    }

    //Constructor
    Node(int d) {
      	data = d;
        parent = d;
        rank = 0;
    }

    //Getters and setters for Node object
    int getData() const { return data; }
    void setData(int d) { data = d; }
    
    int getParent() const { return parent; }
    void setParent(int p) { parent = p; }
    
    int getRank() const { return rank; }
    void setRank(int r) { rank = r; }
};

//
class Edge {
  private:
    int a; //Node A
    int b; //Node B
    int w; //Weight
    bool i; //Inserted?

  public:
    //Default constructor
    Edge() {
        a = 0;
        b = 0;
        w = 0;
        i = 0;
    }

    //Constructor
    Edge(int  p, int  q, int  weight) {
        a = p;
        b = q;
        w = weight;
        i = 0;
    }

    //Getters and setters for Edge object
    int getA() const { return a; }
    void setA(int  node) { a = node; }

    int getB() const { return b; }
    void setB(int  node) { b = node; }

    int getW() const { return w; }
    void setW(int  weight) { w = weight; }

    bool getI() const { return i; }
    void setI(bool inserted) { i = inserted; }
};

class UFDS {
  private:
    Node **NodeArray;
    vector<Edge> EdgeVec; //Create empty vector of edges
    int nodes;
    int edges;
    int insertIndex; //Next index of edge vector to parse into

  public:
    //Constructor for Union-Find Data Structure
    UFDS(int  n, int  m) { //n = nodes, m = edges
        nodes = n;
        edges = m;
        insertIndex = 0;
        //Fill empty node array with nodes
        NodeArray = new Node*[nodes];
        for (int i=1; i<nodes+1; i++) {
            NodeArray[i] = new Node(i);
        }
        EdgeVec.resize(edges);
    }

    //Parse edge into vector of edges
    void newEdge(int a, int b, int w) {
        EdgeVec[insertIndex].setA(a);
        EdgeVec[insertIndex].setB(b);
        EdgeVec[insertIndex].setW(w);

        insertIndex++;
    }

    int find(int x) {
        //If this node has depth of at least 2, go up tree to find root.
        if (NodeArray[x]->getParent() != NodeArray[NodeArray[x]->getParent()]->getParent()) {
            NodeArray[x]->setParent(find(NodeArray[x]->getParent()));
        }
        return NodeArray[x]->getParent(); //Return root
    }

    bool unify(int a, int b) {
        //Check if A and B are in the same subtree
  	    if (find(a) == find(b)) {
            cout << "Edge (" << a << "," << b << ") creates cycle" << endl;
            return 0;
        }
        //If A and B have the same depth
        else if (NodeArray[a]->getRank() == NodeArray[b]->getRank()) {
            //Only depth of A is incremented
            NodeArray[a]->setRank(NodeArray[a]->getRank() + 1);
            NodeArray[find(b)]->setParent(a);
            NodeArray[b]->setParent(a);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        //If depth of A is greater than depth of B
        else if (NodeArray[a]->getRank() > NodeArray[b]->getRank()) {
            //Add depth of B to depth of A
            NodeArray[a]->setRank(NodeArray[a]->getRank() + NodeArray[b]->getRank());
            NodeArray[find(b)]->setParent(a);
            NodeArray[b]->setParent(a);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        //If depth of B is greater than depth of A
        else if (NodeArray[a]->getRank() < NodeArray[b]->getRank()) {
            //Add depth of A to depth of B
            NodeArray[b]->setRank(NodeArray[b]->getRank() + NodeArray[a]->getRank());
            NodeArray[find(a)]->setParent(b);
            NodeArray[a]->setParent(b);
            cout << "Edge (" << a << "," << b << ") successfully inserted" << endl;
            return 1;
        }
        //If unify fails for some reason
        cout << "Error: Unable to perform union." << endl;
        return 0;
    }

    //Comparison function for std::sort()
    static bool sortLikeDis (const Edge& a, const Edge& b) {
        //Return true if weight of A < weight of B
        if (a.getW() < b.getW())
            return a.getW() < b.getW();
        //If weights are equal...
        else if (a.getW() == b.getW()) {
            //Compare source nodes
            if (a.getA() < b.getA())
                return a.getA() < b.getA();
            //If sources nodes are equal, compare destination nodes
            else if (a.getA() == b.getA()) {
                if (a.getB() < b.getB())
                    return a.getB() < b.getB();
            }
        }
        return false;
    }

    //Sorts vector of edges and performs union on nodes
    void Kruskal() {
        //Sort vector of edges
        sort(EdgeVec.begin(), EdgeVec.end(), sortLikeDis);
        //Traverse sorted list of edges to perform union.
        for (int i=0; i<edges; i++) {
            //If edge does NOT create cycle, mark it as inserted
        	if (unify(EdgeVec[i].getA(), EdgeVec[i].getB()) == 1) {
                EdgeVec[i].setI(1);
            }
        }
    }

    //Print out all inserted edges
    void print() const {
        int totalweight=0, count=0;
        //Check if it is a MST
        //(Number of inserted edges) = (number of nodes)-1
        for (int i=0; i<edges; i++) {
            if (EdgeVec[i].getI()==1) {
                count++;
            }
        }
        //(Number of inserted edges) = (number of nodes)-1
        if (count != (nodes-1)) {
            cout << "Error: MST not found." << endl;
            exit(0);
        }

        //If it is a MST, print edges
        for (int i=0; i<edges; i++) {
            if (EdgeVec[i].getI()==1) {
                cout << EdgeVec[i].getA() << " " << EdgeVec[i].getB() << endl;;
                totalweight += EdgeVec[i].getW(); //Add weight
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