#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

Manager::Manager()	//constructor
{
	flog.open("log.txt", ios::app);	//for log.txt
	flog.setf(ios::fixed);

	avl = new AVLTree(&flog);
	gp = new Graph(&flog);
	iter = 0;
	cmd = NULL;
}

Manager::~Manager()	//destructor
{
	flog.close();
}

void Manager::run(const char * command)	//driver
{
	fin.open(command);	//open command.txt

	cmd = new char[40];	//cmd = command Text


	while (!fin.eof())	//read command file
	{
		iter = iter + 1;
		fin.getline(cmd, 40);	//read file
		char * one = strtok(cmd, " ");	//tokenize command

		if (!strcmp(one, "LOAD")) {	//if command is LOAD
			if (LOAD()) printSuccessCode(one);	//call LOAD function
			else printErrorCode(100, one);	//print error 100
			flog << endl;
		}
		else if (!strcmp(one, "INSERT")) {	//if command is INSERT
			int location = atoi(strtok(NULL, " "));	//location id
			char city[50], country[50];
			strcpy(city, strtok(NULL, " "));	//city_name
			strcpy(country, strtok(NULL, " "));	//country
			if (INSERT(location, city, country)) {	//call insert function
				flog << "==> command " << iter << ") " << one << endl;
				flog << "( " << location << ", "
					<< city << ", "
					<< country << " )" << endl;
			}
			else printErrorCode(200, one);	//print error 200
			flog << endl;
		}
		else if (!strcmp(one, "PRINT_AVL")) {	//if command is PRINT_AVL
			char * err = strtok(NULL, " ");
			if (!err) {
				if (PRINT_AVL()) {	//call PRINT_AVL function
					flog << "==> command " << iter << ") " << one << endl;
					avl->Inorder_Traversal(avl->Getroot());	//call real print function
				}
				else printErrorCode(300, one);	//print error 300
				flog << endl;
			}
			else printErrorCode(300, one);	//print error 300
			flog << endl;
		}
		else if (!strcmp(one, "SEARCH_AVL")) {	//if command is SEARCH_AVL
			char * location = strtok(NULL, " ");	//location id
			char * err = strtok(NULL, " ");
			bool err_flag = false;
			if (err != NULL) err_flag = true;
			if (location == NULL) err_flag = true;
			if (!err_flag) {
				AVLNode * flag = NULL;
				if (flag = SEARCH_AVL(atoi(location))) {	//get node
					flog << "==> command " << iter << ") " << one << endl;
					avl->print_avl_node(flag);	//print node
				}
				else printErrorCode(500, one);	//print error 500
				flog << endl;
			}
			else printErrorCode(500, one);	//print error 500
			flog << endl;
		}
		else if (!strcmp(one, "DELETE_AVL")) {	//if command is DELETE_AVL
			bool err_flag = false;
			char * location = strtok(NULL, " ");
			if (location == NULL) err_flag = true;
			char * err = strtok(NULL, " ");
			if (err != NULL) err_flag = true;
			if (!err_flag) {
				if (DELETE_AVL(atoi(location))) printSuccessCode(one);	//delete node
				else printErrorCode(400, one);	//print error 400
				flog << endl;
			}
			else printErrorCode(400, one);
			flog << endl;
		}
		else if (!strcmp(one, "BUILD_GP")) {	//if command is BUILD_GP
			char * err = strtok(NULL, " ");
			if (!err) {
				if (BUILD_GP()) printSuccessCode(one);	//make graph
				else printErrorCode(600, one);	//print error 600
				flog << endl;
			}
			else printErrorCode(600, one);
			flog << endl;
		}
		else if (!strcmp(one, "PRINT_GP")) {	//if command is PRINT_GP
			char * err = strtok(NULL, " ");
			if (!err) {
				if (PRINT_GP()) {	//call PRINT_GP function
					flog << "==> command " << iter << ") " << one << endl;
					gp->Print_GP();	//print graph
				}
				else printErrorCode(700, one);	//print error 700
				flog << endl;
			}
			else printErrorCode(700, one);
			flog << endl;
		}
		else if (!strcmp(one, "BUILD_MST")) {	//if command is BUILD_MST
			char * err = strtok(NULL, " ");
			if (!err) {
				if (BUILD_MST()) printSuccessCode(one);	//make minimum spanning tree
				else printErrorCode(800, one);	//print error 800
				flog << endl;
			}
			else printErrorCode(800, one);
			flog << endl;
		}
		else if (!strcmp(one, "PRINT_MST")) {	//if command is PRINT_MST
		char * err = strtok(NULL, " ");
		if (!err) {
				if (PRINT_MST()) {	//call PRINT_MST function
					flog << "==> command " << iter << ") " << one << endl;
					gp->Print_MST();	//print mst
				}
				else printErrorCode(900, one);	//print error 900
				flog << endl;
			}
			else printErrorCode(900, one);
			flog << endl;
		}
		else if (!strcmp(one, "EXIT")) {	//if command is EXIT
			printSuccessCode(one);
			EXIT();		//quit program
		}
		else {	//error handling
			printErrorCode(0,"Unknown");
		}
	}
	fin.close();
	return;
}

// read city_list text file and make AVL Tree
bool Manager::LOAD()
{
	ifstream fcity("city_list.txt");	//city_list.txt
	string line;
	while (getline(fcity, line)) {
		CityData * city_data = new CityData();	//allocate CityData info node
		char line_char[100];
		strcpy(line_char, line.c_str());	//convert string to char

		char * temp = strtok(line_char, "\t");	//tokenize with tap
		city_data->SetLocationId(atoi(temp));	//location, convert string to int

		temp = strtok(NULL, "\t");	//tokenize with tap
		city_data->Setname(temp);	//copy temp at name

		temp = strtok(NULL, "\t");	//tokenize with tap
		city_data->Setcountry(temp);	//copy temp at country

		if (avl->Getroot() == NULL) {	//if empty tree
			AVLNode * pNew = new AVLNode();
			pNew->SetCityData(city_data);
			avl->Setroot(pNew);		//set new node as root
		}
		else {
			avl->Insert(city_data);	//insert to avl tree
		}
	}
	return true;
}

// AVL insert Node
bool Manager::INSERT(int location, char* city, char* country)
{
	if (avl->Getroot() == NULL) {	//if empty tree
		return false;
	}
	else {	//else, AVL_insert
		CityData * city_data = new CityData();	//allocate new CityData
		city_data->SetLocationId(location);	//set elements
		city_data->Setname(city);
		city_data->Setcountry(country);
		avl->Insert(city_data);
		return true;
	}
}

// Print AVL Tree
bool Manager::PRINT_AVL()
{
	if (avl->Print()) return true;	//call avl->Print function
	else return false;
}

// Search Node from AVL Tree
AVLNode * Manager::SEARCH_AVL(int num)
{
	if (avl->Search(num) != NULL) return avl->Search(num);	//call seach function
	else return NULL;
}

// Delete Node from AVL Tree
bool Manager::DELETE_AVL(int num)
{
	if (avl->Delete(num)) return true;	//call avl Delete function
	else return false;
}

// Create Graph Using AVL TreeNode (CityData)
bool Manager::BUILD_GP()
{
	if (gp->Build(avl)) return true;	//call Build function
	else return false;
}

// Print Graph
bool Manager::PRINT_GP()
{
	if (gp->mList != NULL) return true;
	else return false;
}

// Make Minumum Spanning Tree from Graph
bool Manager::BUILD_MST()
{
	if (gp->Kruskal())	return true;
	else return false;
}

// Print MST
bool Manager::PRINT_MST()
{
	if (gp->mstMatrix != NULL)	return true;
	else return false;
}

// Quit Program
void Manager::EXIT()
{
	exit(1);
}

void Manager::printErrorCode(int n, const char * cmdname) {//ERROR CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Error code: " << n << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Success" << endl;
}