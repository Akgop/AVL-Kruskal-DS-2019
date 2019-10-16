#include "AVLNode.h"
#include <iostream>
#include <fstream>// header file declare
#include <queue>
#include <algorithm>
using namespace std;
class AVLTree
{
public:
	AVLNode * root;	// AVLTree Root
	ofstream * flog;

public:
	AVLTree(ofstream * flog);
	~AVLTree();

	AVLNode  *  Getroot();
	void	 	Setroot(AVLNode * node);
	bool		Insert(CityData * node);
	bool		Delete(int num);
	AVLNode *	Search(int num);
	bool		Print();

	void Inorder_Traversal(AVLNode * t);
	void print_avl_node(AVLNode * t);

	int get_height(AVLNode * t);
	void update_BF();
};

