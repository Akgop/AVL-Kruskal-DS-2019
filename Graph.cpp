#include "Graph.h"
#include <map>
#include <iomanip>
Graph::Graph(ofstream * flog)	//Constructor
{
	this->flog = flog;
	this->mList = NULL;
	this->mstMatrix = NULL;
	this->vertex = NULL;
	this->edge.clear();
	this->root = NULL;
}

Graph::~Graph()	//destructor
{
}

bool Graph::Build(AVLTree * root)	//Build Graph
{
	// #0. Special case - If Graph already exists
	if (this->mList != NULL) {	//De-allocate graph and mst
		delete[] this->mList;
		delete[] this->vertex;
		delete[] this->root;
		this->mList = NULL;
		this->vertex = NULL;
		this->edge.clear();
		this->root = NULL;
	}
	// #1. Set AVL Tree size
	Set_AVL_Size(root);
	
	// #2. Allocate Maps
	if (Get_AVL_Size() == 0) {	//if empty tree
		return false;
	}
	this->mList = new map<int, CityData *>[Get_AVL_Size()];	//allocate new matrix for Graph
	this->vertex = new CityData* [Get_AVL_Size()];	//allocate Vertex map

	// #3. make Graph
	AVLNode * pCur = root->Getroot();
	int cnt = 0, dist = 0;
	pair<int, CityData*> p;
	CityData * pNew = new CityData;
	Inorder_AVL(pCur, vertex, cnt);
	for (int i = 0; i < Get_AVL_Size(); i++) {	//from node
		for (int j = 0; j < Get_AVL_Size(); j++) {	//to node
			if (i != j) {	//except node to node itself
				this->mList[i].insert(make_pair(j, vertex[j]));	//insert Citydata to map
			}
		}
	}
	return true;
}

void Graph::Print_GP()	//Print Graph
{
	map<int, CityData*> *m = this->mList;
	map<int, CityData*>::iterator it;	//map iterator 
	int cnt, dist = 0;	//cnt for count iterator
	flog->setf(ios::left);
	//
	//	show graph as 2D-array matrix
	//
	for (int i = 0; i < Get_AVL_Size(); i++) {	//mList[i][cnt]
		cnt = 0;
		for (it = m[i].begin(); it != m[i].end();) {
			if (i == cnt) *flog << setw(6) << "0";	//node itself
			else {
				dist = Get_Distance(this->vertex[i], it->second);	//get distance
				*flog << setw(3) << dist;
				it++;
			}
			cnt++;
		}
		if (i == Get_AVL_Size() - 1) *flog << "0";
		*flog << endl;
	}

}

void Graph::Print_MST()	//Print MST
{
	if (Get_AVL_Size() != 1) {	//Recursive Driver
		this->find_path_mst();
	}
}

int Graph::Get_AVL_Size()	//avl size (number of nodes of avltree)
{
	return this->size;
}

void Graph::Set_AVL_Size(AVLTree * root)	//set size
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

void Graph::Inorder_AVL(AVLNode * t, CityData ** c, int &cnt)	//Make Vertex map
{
	if (t != NULL) {						//recursive workhorse for vertex map
		Inorder_AVL(t->GetLeft(), c, cnt);
		c[cnt] = t->GetCityData();
		cnt++;
		Inorder_AVL(t->GetRight(), c, cnt);
	}
}

//Get distance from two City
int Graph::Get_Distance(CityData *from, CityData* to)
{
	if (from->GetLocationId() > to->GetLocationId())	//from > to
		return from->GetLocationId() - to->GetLocationId();	//from - to
	else if (from->GetLocationId() < to->GetLocationId())	//to > from
		return to->GetLocationId() - from->GetLocationId();	//to - from
	else return 0;	//node itself = 0
}

void Graph::find_path_mst()	//mst recursive workhorse // Print MST
{
	int start_vertex, cur_vertex;
	int * cnt = new int[Get_AVL_Size()];	//counter for edges at each nodes
	bool * visited = new bool[Get_AVL_Size() - 1];	//visited flag for each edges
	cnt[0] = 0;
	//
	// #1. Initialize
	//
	for (int i = 0; i < Get_AVL_Size() - 1; i++) {	//initialize visited flag
		cnt[i + 1] = 0;
		visited[i] = true;	//true -> not visited
	}
	for (int i = 0; i < Get_AVL_Size() - 1; i++) {	//count edges at each nodes
		cnt[this->mstMatrix[i].second.first] ++;
		cnt[this->mstMatrix[i].second.second] ++;
	}
	for (int i = 0; i < Get_AVL_Size(); i++) {	//find start vertex
		if (cnt[i] == 1) {
			start_vertex = i;	//if count == 1 -> start vertex
			break;
		}
	}
	//
	// #2. Print MST from start vertex to end vertex
	//
	int sum = 0;	//total distance
	cur_vertex = start_vertex;
	for (int j = 0; j < Get_AVL_Size() - 1; j++) {
		for (int i = 0; i < Get_AVL_Size() - 1; i++) {	//find vertex
			if (visited[i]) {	//if not visited
				if (cur_vertex == this->mstMatrix[i].second.first) {
					*flog << "( " << this->vertex[this->mstMatrix[i].second.first]->Getname()	//PRINT edge
						<< ", " << this->vertex[this->mstMatrix[i].second.second]->Getname()
						<< " ), " << this->mstMatrix[i].first << endl;
					visited[i] = false;	//set flag
					cur_vertex = this->mstMatrix[i].second.second;	//set next vertex
					sum += this->mstMatrix[i].first;	//add weight to sum
					break;
				}
				else if (cur_vertex == this->mstMatrix[i].second.second) {
					*flog << "( " << this->vertex[this->mstMatrix[i].second.second]->Getname()	//PRINT edge
						<< ", " << this->vertex[this->mstMatrix[i].second.first]->Getname()
						<< " ), " << this->mstMatrix[i].first << endl;
					visited[i] = false;	//set flag
					cur_vertex = this->mstMatrix[i].second.first;	//set next vertex
					sum += this->mstMatrix[i].first;	//add weight to sum
					break;
				}
				else {
					continue;
				}
			}
		}
	}
	*flog << "Total: " << sum << endl;
	//
	// #3. De-allocate array, END
	//
	delete[] cnt;
	delete[] visited;
}


//for kruskal algorithm.
void Graph::Ascending_Edges()
{
	int cnt = 0;	//use weight as key to sort vector
	for (int i = 0; i < Get_AVL_Size(); i++) {
		for (int j = i; j < Get_AVL_Size(); j++) {
			if (i != j) {
				edge.push_back(make_pair(Get_Distance(vertex[i], vertex[j]), make_pair(i, j))); //push edge as vector
				cnt++;
			}
		}
	}
	sort(edge.begin(), edge.end());	//sort edge
}

bool Graph::Kruskal()	//Kruskal Algorithm
{
	if (Get_AVL_Size() == 0) return false;	//error handling
	if (Get_AVL_Size() == 1) return false;
	make_set();	//call make_set function
	Ascending_Edges();	//sort edge by weight(key)
	mstMatrix = new pair<int, pair<int, int>>[Get_AVL_Size() - 1];	//allocate new matrix for mst
	int cnt = 0;
	int size = (Get_AVL_Size() * (Get_AVL_Size() - 1)) / 2;	//size = number of edge
	for (int i = 0; i < size; i++) {
		if (find(this->edge[i].second.first) != find(this->edge[i].second.second)) {	//not a cyclic path
			union_set(this->edge[i].second.first, this->edge[i].second.second);
			mstMatrix[cnt] = this->edge[i];
			cnt++;
		}
		else { continue; }	//cyclic path occurs
	}
	return true;
}

void Graph::make_set()	//make set for kruskal algorithm
{
	this->root = new int[Get_AVL_Size()];
	for (int i = 0; i < Get_AVL_Size(); i++) {
		this->root[i] = i;	//initialize root array
	}
}

void Graph::union_set(int x, int y)	//connect two disjoint tree
{
	x = find(x);	//find x root
	y = find(y);	//find y root

	root[y] = x;	//make two as same root
}

int Graph::find(int x)	//get root of disjoint tree
{
	if (root[x] == x) {
		return x;
	}
	else {
		return find(root[x]);	//call find function
	}
}
