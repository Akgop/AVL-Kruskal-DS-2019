#include "AVLTree.h"

AVLTree::AVLTree(ofstream * flog)
{
	Setroot(NULL);
}

AVLTree::~AVLTree()
{
}

AVLNode * AVLTree::Getroot()
{
	return this->root;
}

void AVLTree::Setroot(AVLNode * node)
{
	this->root = node;
}

bool AVLTree::Insert(CityData * node)
{
	AVLNode * pNew = new AVLNode();
	pNew->SetCityData(node);
	//
	// #1. Locate insertion point for pNew
	//
	AVLNode * pCur = Getroot(),	//Current Node.
		*pA = Getroot(),	//A-Node = most recent node with mBF = +- 1
		*pCur_parent = NULL,	//Parent node of pCur
		*pA_parent = NULL,		//Parent node of A-Node
		*rootSub = NULL;		//new root after rotation

	while (pCur != NULL) {
		if (pCur->GetmBF() != 0) {	//if mBF = +- 1
			pA = pCur;	pA_parent = pCur_parent;
		}
		if (strcmp(node->Getname(),pCur->GetCityData()->Getname()) == -1) {	//take left branch
			pCur_parent = pCur;
			pCur = pCur->GetLeft();
		}
		else if (strcmp(node->Getname(), pCur->GetCityData()->Getname()) == 1) {	//else take right branch
			pCur_parent = pCur;
			pCur = pCur->GetRight();
		}
		else if (strcmp(node->Getname(), pCur->GetCityData()->Getname()) == 0){
			return false; 
		}
	}
	//
	// #2. Insert pNew
	//
	if (strcmp(node->Getname(), pCur_parent->GetCityData()->Getname()) == -1) {
		pCur_parent->SetLeft(pNew);
	}
	else pCur_parent->SetRight(pNew);
	//
	// #3. Rebalance
	//
	// #3-1) set B-node, C-node
	int d = 1;
	AVLNode * pB, *pC; //pB = child of pA, pC = child of pB
	if (strcmp(node->Getname(), pA->GetCityData()->Getname()) == 1) {	//if new node inserted at right
		pB = pCur = pA->GetRight();	//pB = pA->right, pCur = pA->right
		d = -1;	//l - r = -1
	}
	else {	//if new node inserted at left
		pB = pCur = pA->GetLeft();	//pB = pA->left, pCur = pA->right
		d = 1;	//l - r = 1
	}

	// #3-2) update balance factor
	while (pCur != pNew) {	//stop loop at pCur == pNew
		if (strcmp(node->Getname(), pCur->GetCityData()->Getname()) == 1) {	//right added
			pCur->SetmBF(-1);	pCur = pCur->GetRight();	//height of right increases by 1
		}
		else {	//left added
			pCur->SetmBF(1);	pCur = pCur->GetLeft();//height of left increases by 1
		}
	}

	// #3-3) Tree Still balanced
	if (pA->GetmBF() == 0 || pA->GetmBF() + d == 0) {	//if tree still balanced
		pA->SetmBF(pA->GetmBF() + d);	//set pA->mBF
		return true;
	}
	
	// #3-4) Tree Unbalnced, Rotate Subtree
	if (d == 1) {	//if left imbalance
		// LL Rotation
		if (pB->GetmBF() == 1) {
			pA->SetLeft(pB->GetRight());	//a->left = b->right
			pB->SetRight(pA);		//b->right = a
			pA->SetmBF(0);	pB->SetmBF(0);	//update bf
			rootSub = pB;	//b is new root of the subtree
		}
		// LR Rotation
		else {
			pC = pB->GetRight();	//initial state
			pB->SetRight(pC->GetLeft());	//b->right = c->left
			pA->SetLeft(pC->GetRight());	//a->left = c->right
			pC->SetLeft(pB);	//c->left = b
			pC->SetRight(pA);	//c->right = a
			switch (pC->GetmBF()) {
			case 0:		//if pC was balanced
				pB->SetmBF(0);	pA->SetmBF(0);
				break;
			case 1:		//if pC was left imbalance
				pA->SetmBF(-1);	pB->SetmBF(0);
				break;
			case -1:	//if pC was right imbalance
				pB->SetmBF(1);	pA->SetmBF(0);
				break;
			}
			pC->SetmBF(0);	rootSub = pC;	//pC is new root of Subtree
		}
	}
	else {	//if right imbalance
		// RR Rotation
		if (pB->GetmBF() == -1) {
			pA->SetRight(pB->GetLeft());	//a->right = b->left
			pB->SetLeft(pA);	//b->left = a
			pA->SetmBF(0);	pB->SetmBF(0);	//update balance factor
			rootSub = pB;	//b is new root of subtree
		}
		// RL Rotation
		else {
			pC = pB->GetLeft();	//initial state
			pB->SetLeft(pC->GetRight());	//b->left = c->right
			pA->SetRight(pC->GetLeft());	//a->right = c->left
			pC->SetRight(pB);	//c->right = b
			pC->SetLeft(pA);	//c->left = a
			switch (pC->GetmBF()) {
			case 0:	//if pC was balanced
				pB->SetmBF(0);	pA->SetmBF(0);
				break;
			case 1:	//if pC was left imbalanced
				pB->SetmBF(-1);	pA->SetmBF(0);
				break;
			case -1:	//if pC was right imbalanced
				pA->SetmBF(1);	pB->SetmBF(0);
				break;
			}
			pC->SetmBF(0);	rootSub = pC;	//pC is new root of subtree
		}
	}
	// #3-5) Set child of Parent of A-Node to Subroot
	if (pA_parent == NULL) this->root = rootSub;	//if pA was root, set rootSub as new root
	else if (pA == pA_parent->GetLeft()) pA_parent->SetLeft(rootSub);	//if pA was leftchild, parent->left = rootSub
	else pA_parent->SetRight(rootSub);	//if pA was rightchild, parent->right = rootSub

	return true;
}

CityData * AVLTree::Delete(int num)
{
	return NULL;
}

CityData * AVLTree::Search(int num)
{
	return NULL;
}

bool AVLTree::Print()
{
	AVLNode * pCur = this->root;
	if (this->root != NULL) {
		Inorder_Traversal(pCur);
		return true;
	}
	else {
		return false;
	}
}

void AVLTree::Inorder_Traversal(AVLNode * t)
{
	if (t != NULL) {
		Inorder_Traversal(t->GetLeft());
		cout << "(" << t->GetCityData()->GetLocationId() << ", ";
		cout << t->GetCityData()->Getname() << ", ";
		cout << t->GetCityData()->Getcountry() << ")" << endl;
		Inorder_Traversal(t->GetRight());
	}
	return;
}
