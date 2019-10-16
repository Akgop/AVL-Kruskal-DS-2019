#include "AVLTree.h"

AVLTree::AVLTree(ofstream * flog)
{
	Setroot(NULL);
	this->flog = flog;
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

bool AVLTree::Delete(int num)
{
	//
	// #1. find target node to delete
	//
	AVLNode * pTemp = Search(num);
	if (pTemp == NULL) return false;
	char cTemp[50];
	strcpy(cTemp, pTemp->GetCityData()->Getname());
	stack<AVLNode *> s;
	AVLNode * pCur = Getroot(), *pParent = NULL;

	while (pCur && pCur != pTemp) {	//if pCur == pTemp, break
		if (strcmp(cTemp, pCur->GetCityData()->Getname()) == -1) {	//cTemp < pCur->name
			s.push(pCur);	//stack push
			pParent = pCur;	//pP = p
			pCur = pCur->GetLeft();	//p -> p->left
		}
		else if (strcmp(cTemp, pCur->GetCityData()->Getname()) == 1) {	//cTemp > pCur->name
			s.push(pCur);	//stack push
			pParent = pCur;	//pP = p
			pCur = pCur->GetRight();	//p = p->right
		}
	}
	//
	// #2. Delete node
	//
	// #2-1. No mathing node
	if (pCur == NULL) return false;
	// #2-2. Leaf node
	if (pCur->GetLeft() == NULL && pCur->GetRight() == NULL) {
		if (pParent == NULL) {
			Setroot(NULL); return true;
		}
		else if (pParent->GetLeft() == pCur)	pParent->SetLeft(NULL);
		else if (pParent->GetRight() == pCur)	pParent->SetRight(NULL);
		delete pCur;
	}
	// #2-3. Only right subtree
	else if (pCur->GetLeft() == NULL) {
		if (pParent == NULL)	Setroot(pCur->GetRight());
		else if (pParent->GetLeft() == pCur)	pParent->SetLeft(pCur->GetRight());
		else if (pParent->GetRight() == pCur)	pParent->SetRight(pCur->GetRight());
		delete pCur;
	}
	// #2-4. Only left subtree
	else if (pCur->GetRight() == NULL) {
		if (pParent == NULL)	Setroot(pCur->GetLeft());
		else if (pParent->GetLeft() == pCur)	pParent->SetLeft(pCur->GetLeft());
		else if (pParent->GetRight() == pCur)	pParent->SetRight(pCur->GetLeft());
		delete pCur;
	}
	// #2-5. both child node exist
	else {
		s.push(pCur);
		AVLNode * pTarget = pCur->GetLeft(), *pTargetParent = pCur;
		while (pTarget->GetRight()) {
			s.push(pTarget);
			pTargetParent = pTarget;
			pTarget = pTarget->GetRight();
		}
		pCur->SetCityData(pTarget->GetCityData());
		if (pTargetParent == pCur)	pTargetParent->SetLeft(pTarget->GetLeft());
		else pTargetParent->SetRight(pTarget->GetLeft());
		strcpy(cTemp, pTarget->GetCityData()->Getname());
		delete pTarget;
	}
	//
	// #3. Rebalance
	//
	// #3-1 Set A-Node
	update_BF();
	AVLNode * pA = NULL,
		*pA_parent = NULL,
		*rootSub = NULL;
	bool balanced = true;
	while (!s.empty()) {
		pA = s.top();
		s.pop();
		if (pA->GetmBF() == 2 && pA->GetmBF() == -2) {
			balanced = false;
			break;
		}
	}
	if (balanced) return true;	//if tree still balanced
	if (!s.empty())	pA_parent = s.top();
	// #3-2. set B-Node, C-Node
	AVLNode * pB, *pC;
	// #3-4. Tree Unbalnced, Rotate Subtree
	if (pA->GetmBF() == 2) {	//if left imbalance
		pB = pA->GetLeft();
		// LL Rotation
		if (pB->GetmBF() == 1) {
			pA->SetLeft(pB->GetRight());	//a->left = b->right
			pB->SetRight(pA);		//b->right = a
			rootSub = pB;	//b is new root of the subtree
		}
		// LR Rotation
		else {
			pC = pB->GetRight();	//initial state
			pB->SetRight(pC->GetLeft());	//b->right = c->left
			pA->SetLeft(pC->GetRight());	//a->left = c->right
			pC->SetLeft(pB);	//c->left = b
			pC->SetRight(pA);	//c->right = a
		}
	}
	else {	//if right imbalance
		pB = pA->GetRight();
		// RR Rotation
		if (pB->GetmBF() == -1) {
			pA->SetRight(pB->GetLeft());	//a->right = b->left
			pB->SetLeft(pA);	//b->left = a
			rootSub = pB;	//b is new root of subtree
		}
		// RL Rotation
		else {
			pC = pB->GetLeft();	//initial state
			pB->SetLeft(pC->GetRight());	//b->left = c->right
			pA->SetRight(pC->GetLeft());	//a->right = c->left
			pC->SetRight(pB);	//c->right = b
			pC->SetLeft(pA);	//c->left = a
			rootSub = pC;	//pC is new root of subtree
		}
	}
	// #3-5. Set child of Parent of A-Node to Subroot
	if (pA_parent == NULL) this->root = rootSub;	//if pA was root, set rootSub as new root
	else if (pA == pA_parent->GetLeft()) pA_parent->SetLeft(rootSub);	//if pA was leftchild, parent->left = rootSub
	else pA_parent->SetRight(rootSub);	//if pA was rightchild, parent->right = rootSub
	//
	// #4. Update BF
	//
	update_BF();
	return true;
}

AVLNode * AVLTree::Search(int num)
{
	//Level Order Search
	//avl is height balanced, so I used level order
	queue<AVLNode *> q;	//declare queue
	AVLNode * pCur = Getroot();	//start from root
	while (pCur) {
		if (pCur->GetCityData()->GetLocationId() == num) {
			return pCur;	//found node. return
		}
		if (pCur->GetLeft()) q.push(pCur->GetLeft());	//if left child exist, push left child to queue
		if (pCur->GetRight()) q.push(pCur->GetRight());	//if right childe exist, push right child to queue
		if (q.empty()) return NULL;	//cannot find, return null
		pCur = q.front();	q.pop();	//pcur = q.front.
	}
}

bool AVLTree::Print()
{
	AVLNode * pCur = this->root;
	if (this->root != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void AVLTree::Inorder_Traversal(AVLNode * t)
{
	//used in-order traversal to print all node bottom to top.
	if (t != NULL) {
		Inorder_Traversal(t->GetLeft());
		print_avl_node(t);
		Inorder_Traversal(t->GetRight());
	}
	return;
}

void AVLTree::print_avl_node(AVLNode * t)
{
	//write data at log.txt
	*flog << "(" << t->GetCityData()->GetLocationId() << ", ";
	*flog << t->GetCityData()->Getname() << ", ";
	*flog << t->GetCityData()->Getcountry() << ")" << endl;
}

int AVLTree::get_height(AVLNode * t)
{
	if (t == NULL) {
		return 0;
	}
	return 1 + max(get_height(t->GetLeft()), get_height(t->GetRight()));
}

void AVLTree::update_BF()
{
	queue<AVLNode *> q;
	AVLNode * pCur = Getroot();
	int lh = 0, rh = 0;
	while (pCur) {
		lh = get_height(pCur->GetLeft());
		rh = get_height(pCur->GetRight());
		pCur->SetmBF(lh - rh);
		if (pCur->GetLeft()) q.push(pCur->GetLeft());	//if left child exist, push left child to queue
		if (pCur->GetRight()) q.push(pCur->GetRight());	//if right childe exist, push right child to queue
		if (q.empty()) break;	//cannot find, return null
		pCur = q.front();	q.pop();	//pcur = q.front.
	}
}
