#include "Graph.h"
#include<utility>
#include<iostream>
#include<fstream>
#include<string.h>
#include<string>

using namespace std;

class Manager
{
public:
	AVLTree * avl;	//avl
	Graph * gp;	//gp

	char * cmd;
	int iter;

public:
	Manager();
	~Manager();

	ofstream flog;
	ifstream fin;

	//Command set
	void run(const char * command);
	bool LOAD();
	bool INSERT(int location, char * city, char * country);
	bool PRINT_AVL();
	AVLNode * SEARCH_AVL(int num);
	bool DELETE_AVL(int num);
	bool BUILD_GP();
	bool PRINT_GP();
	bool BUILD_MST();
	bool PRINT_MST();
	void EXIT();

	void printErrorCode(int n, const char * cmdname);
	void printSuccessCode(const char * cmdname);

};
