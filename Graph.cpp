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
	vector<AVLNode * > v;
	AVLNode * pCur = root->Getroot();
	if (pCur != NULL) {
		Inorder_AVL(pCur, v);
	}
	else return false;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			this->mList->insert(make_pair(j, v.at(j)->GetCityData()));
		}
	}
	map<int, CityData *> *m = this->mList;
	map<int, CityData *>::iterator it;
	for (it = m->begin(); it != m->end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	return true;
}

void Graph::Print_GP()
{
}

void Graph::Print_MST()
{
}

void Graph::Inorder_AVL(AVLNode * t, vector<AVLNode *> v)
{
	if (t != NULL) {
		Inorder_AVL(t->GetLeft(), v);
		v.push_back(t);
		Inorder_AVL(t->GetRight(), v);
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
