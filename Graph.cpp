#include "Graph.h"
#include <map>

Graph::Graph(ofstream * flog)
{
	this->flog = flog;
}

Graph::~Graph()
{
}

bool Graph::Build(AVLTree * root)
{
	if (root != NULL) {
		AVLNode * pCur = root->Getroot();
		Inorder_AVL(pCur);
		return true;
	}
	return false;
}

void Graph::Print_GP()
{
}

void Graph::Print_MST()
{
}

void Graph::Inorder_AVL(AVLNode * t)
{
	if (t != NULL) {
		Inorder_AVL(t->GetLeft());
		//
		Inorder_AVL(t->GetRight());
	}
}

bool Graph::Kruskal()
{
	return false;
}

void Graph::make_set()
{
}

void Graph::union_set(int x, int y)
{
}

void Graph::find(int x)
{
}
