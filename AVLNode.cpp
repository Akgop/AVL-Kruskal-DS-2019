#include "AVLNode.h"

AVLNode::AVLNode()
{
	this->pCityData = NULL;
	this->pLeft = NULL;
	this->pRight = NULL;
	this->mBF = 0;
}

AVLNode::~AVLNode()
{
}

CityData * AVLNode::GetCityData()
{
	return this->pCityData;
}

AVLNode * AVLNode::GetLeft()
{
	return this->pLeft;
}

AVLNode * AVLNode::GetRight()
{
	return this->pRight;
}

int AVLNode::GetmBF()
{
	return this->mBF;
}

void AVLNode::SetCityData(CityData * node)
{
	this->pCityData = node;
}

void AVLNode::SetLeft(AVLNode * node)
{
	this->pLeft = node;
}

void AVLNode::SetRight(AVLNode * node)
{
	this->pRight = node;
}

void AVLNode::SetmBF(int n)
{
	this->mBF = n;
}
