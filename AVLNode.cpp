#include "AVLNode.h"

AVLNode::AVLNode()	//constructor
{
	this->pCityData = NULL;
	this->pLeft = NULL;
	this->pRight = NULL;
	this->mBF = 0;
}

AVLNode::~AVLNode()	//destructor
{
}

CityData * AVLNode::GetCityData()	//getcitydata
{
	return this->pCityData;
}

AVLNode * AVLNode::GetLeft()	//left
{
	return this->pLeft;
}

AVLNode * AVLNode::GetRight()	//right
{
	return this->pRight;
}

int AVLNode::GetmBF()	//balance factor
{
	return this->mBF;
}

void AVLNode::SetCityData(CityData * node)	//set citydata
{
	this->pCityData = node;
}

void AVLNode::SetLeft(AVLNode * node)	//set left
{
	this->pLeft = node;
}

void AVLNode::SetRight(AVLNode * node)	//set right
{
	this->pRight = node;
}

void AVLNode::SetmBF(int n)	//set balance factor
{
	this->mBF = n;
}