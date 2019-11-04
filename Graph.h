#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
using namespace std;
class Graph
{
public:
	map<int, CityData *> * mList;	// mList[from vetex] = map<to vertex, weight>
	CityData ** vertex;			// vetex[index] = CityData * 
	int size;					// AVLTree size
	pair<int, pair<int, int>> * mstMatrix;			// MST

	vector<pair<int, pair<int, int>>> 	edge;	//<weight, <from, to>>
	/*union set*/
	int * root;				//root info

	ofstream * flog;

public:
	Graph(ofstream * flog);
	~Graph();

	bool	Build(AVLTree * root);	//BUILD GP
	void 	Print_GP();	//PRINT BP
	void	Print_MST();	//PRINT MST

	void	Set_AVL_Size(AVLTree * root);	//get AVLTree size from AVLTree
	int		Get_AVL_Size();	//return AVLTree size
	void	Inorder_AVL(AVLNode * t, CityData ** c, int &cnt);
	int		Get_Distance(CityData* from, CityData* to);	//|a - b| = distance (weight)

	void	find_path_mst();	//Print MST
	void	Ascending_Edges();	//Sort Edges

	/*for Kruskal union_set*/
	bool	Kruskal();
	void 	make_set();
	void 	union_set(int x, int y);
	int		find(int x);
};


