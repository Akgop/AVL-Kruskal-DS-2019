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

	AVLNode  *  Getroot();		//Get root
	void	 	Setroot(AVLNode * node);	//Set root
	bool		Insert(CityData * node);	//Insert AVLNode to AVLTree
	bool		Delete(int num);	//Delete AVLNode from AVLTree
	AVLNode *	Search(int num);	//Search AVLNode from AVLTree
	bool		Print();	//Print tree

	void Inorder_Traversal(AVLNode * t);	//print function
	void print_avl_node(AVLNode * t);	//print avl node function

	int get_height(AVLNode * t);	//left sub - right sub
	void update_BF();	//update BF
};

