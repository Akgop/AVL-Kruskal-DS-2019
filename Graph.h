#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
using namespace std;
class Graph
{
public:
	map<int, CityData *> * mList;	// mList[from vetex] = map<to vertex, weight>
	CityData * vertex;			// vetex[index] = CityData * 
	int size;					// AVLTree size
	int * mstMatrix;			// MST

	ofstream * flog;

public:
	Graph(ofstream * flog);
	~Graph();

	bool	Build(AVLTree * root);
	void 	Print_GP();
	void	Print_MST();

	void	Inorder_AVL(AVLNode * t, vector<AVLNode *> v);

	/*for Kruskal union_set*/
	bool	Kruskal();
	void 	make_set();
	void 	union_set(int x, int y);
	void	find(int x);

};


