#include "Graph.h"
#include <map>

Graph::Graph(ofstream * flog)
{
	this->flog = flog;
	this->mList = NULL;
}

Graph::~Graph()
{
}

bool Graph::Build(AVLTree * root)
{
	// #1. Set AVL Tree size
	Set_AVL_Size(root);
	
	// #2. Allocate Maps
	if (Get_AVL_Size() == 0) {	//if empty tree
		return false;
	}
	if (this->mList != NULL) {	//if mList declared before
		delete[] mList;
		this->mList = NULL;
	}
	this->mList = new map<int, CityData *>[Get_AVL_Size()];
	this->vertex = new CityData[Get_AVL_Size()];

	// #3. make Graph
	AVLNode * pCur = root->Getroot(); 
	int cnt = 0;
	Inorder_AVL(pCur, vertex, cnt);
	for (int i = 0; i < Get_AVL_Size(); i++) {	//from node
		for (int j = 0; j < Get_AVL_Size(); j++) {	//to node
			if (i != j) {	//except node to node itself
				this->mList[i].insert(make_pair(j, &vertex[j]));	//insert Citydata to map
			}
		}
	}
	return true;
}

void Graph::Print_GP()
{
	map<int, CityData*> *m = this->mList;
	map<int, CityData*>::iterator it;	//map iterator 
	int cnt, dist = 0;	//cnt for count iterator
	for (int i = 0; i < Get_AVL_Size(); i++) {	//mList[i][cnt]
		cnt = 0;
		for (it = m[i].begin(); it != m[i].end();) {
			if (i == cnt) *flog << "0\t";	//node itself
			else {
				dist = Get_Distance(this->vertex[i], *it->second);	//get distance
				*flog << dist << "\t";
				it++;
			}
			cnt++;
		}
		if (i == Get_AVL_Size() - 1) *flog << "0";
		*flog << endl;
	}
}

void Graph::Print_MST()
{
}

int Graph::Get_AVL_Size()
{
	return this->size;
}

void Graph::Set_AVL_Size(AVLTree * root)
{
	int count = 0;
	queue<AVLNode *> q;	//declare queue
	AVLNode * pCur = root->Getroot();	//start from root
	while (pCur) {
		count++;
		if (pCur->GetLeft()) q.push(pCur->GetLeft());	//if left child exist, push left child to queue
		if (pCur->GetRight()) q.push(pCur->GetRight());	//if right childe exist, push right child to queue
		if (q.empty()) break;	//cannot find, return null
		pCur = q.front();	q.pop();	//pcur = q.front.
	}
	this->size = count;
}

void Graph::Inorder_AVL(AVLNode * t, CityData * c, int &cnt)
{
	if (t != NULL) {
		Inorder_AVL(t->GetLeft(), c, cnt);
		c[cnt].Setcountry(t->GetCityData()->Getcountry());
		c[cnt].SetLocationId(t->GetCityData()->GetLocationId());
		c[cnt].Setname(t->GetCityData()->Getname());
		cnt++;
		Inorder_AVL(t->GetRight(), c, cnt);
	}
}

//Get distance from two City
int Graph::Get_Distance(CityData from, CityData to)
{
	if (from.GetLocationId() > to.GetLocationId())	//from > to
		return from.GetLocationId() - to.GetLocationId();	//from - to
	else if (from.GetLocationId() < to.GetLocationId())	//to > from
		return to.GetLocationId() - from.GetLocationId();	//to - from
	else return 0;	//node itself = 0
}

bool Graph::Kruskal()
{
	
	return false;
}

void Graph::make_set()
{
	this->root = new int[Get_AVL_Size()];
	for (int i = 0; i < Get_AVL_Size(); i++) {
		this->root[i] = i;
	}
}

void Graph::union_set(int x, int y)
{
	x = find(x);
	y = find(y);

	root[y] = x;
}

int Graph::find(int x)
{
	if (root[x] == x) {
		return x;
	}
	else {
		return find(root[x]);
	}
}
