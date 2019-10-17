#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

Manager::Manager()
{
	flog.open("log.txt", ios::app);
	flog.setf(ios::fixed);

	avl = new AVLTree(&flog);
	gp = new Graph(&flog);
	iter = 0;
	cmd = NULL;
}

Manager::~Manager()
{
	flog.close();
}

void Manager::run(const char * command)
{
	fin.open(command);	//open command.txt

	cmd = new char[40];	//cmd = command Text


	while (!fin.eof())
	{
		iter = iter + 1;
		fin.getline(cmd, 40);
		char * one = strtok(cmd, " ");

		if (!strcmp(one, "LOAD")) {
			if (LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100, "LOAD");
		}
		else if (!strcmp(one, "INSERT")) {
			int location = atoi(strtok(NULL, " "));
			char city[50], country[50];
			strcpy(city, strtok(NULL, " "));
			strcpy(country, strtok(NULL, " "));
			if (INSERT(location, city, country)) {
				flog << "==> command " << iter << ") " << "INSERT" << endl;
				flog << "(" << location << ", ";
				flog << city << ", ";
				flog << country << ")" << endl;
			}
			else printErrorCode(200, "INSERT");
		}
		else if (!strcmp(one, "PRINT_AVL")) {
			if (PRINT_AVL()) {
				flog << "==> command " << iter << ") " << "PRINT_AVL" << endl;
				avl->Inorder_Traversal(avl->Getroot());
			}
			else printErrorCode(300, "PRINT_AVL");
		}
		else if (!strcmp(one, "SEARCH_AVL")) {
			int location = atoi(strtok(NULL, " "));
			AVLNode * flag = NULL;
			if (flag = SEARCH_AVL(location)) {
				flog << "==> command " << iter << ") " << "SEARCH_AVL" << endl;
				avl->print_avl_node(flag);
			}
			else printErrorCode(400, "SEARCH_AVL");
		}
		else if (!strcmp(one, "DELETE_AVL")) {
			int location = atoi(strtok(NULL, " "));
			if (DELETE_AVL(location)) printSuccessCode("DELETE_AVL");
			else printErrorCode(500, "DELETE_AVL");
		}
		else if (!strcmp(one, "BUILD_GP")) {
			if (BUILD_GP()) printSuccessCode("BUILD_GP");
			else printErrorCode(600, "BUILD_GP");
		}
		else if (!strcmp(one, "PRINT_GP")) {
			if (PRINT_GP()) {
				flog << "==> command " << iter << ") " << "PRINT_GP" << endl;
				gp->Print_GP();
			}
			else printErrorCode(700, "PRINT_GP");
		}
		else if (!strcmp(one, "BUILD_MST")) {
			//call function()
		}
		else if (!strcmp(one, "EXIT")) {
			//call function()
			EXIT();	
		}
		else {
			printErrorCode(0,"Unknown");
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream fcity("city_list.txt");
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

		if (avl->Getroot() == NULL) {
			AVLNode * pNew = new AVLNode();
			pNew->SetCityData(city_data);
			avl->Setroot(pNew);
		}
		else {
			avl->Insert(city_data);	//insert to avl tree
		}
	}
	return true;
}

bool Manager::INSERT(int location, char* city, char* country)
{
	CityData * city_data = new CityData();	//allocate new CityData
	city_data->SetLocationId(location);	//set elements
	city_data->Setname(city);
	city_data->Setcountry(country);
	if (avl->Getroot() == NULL) {	//if empty tree
		AVLNode * pNew = new AVLNode();	//new node as root
		pNew->SetCityData(city_data);
		avl->Setroot(pNew);
	}
	else {	//else, AVL_insert
		avl->Insert(city_data);
	}
	return true;
}

bool Manager::PRINT_AVL()
{
	if (avl->Print()) return true;	//call avl->Print function
	else return false;
}

AVLNode * Manager::SEARCH_AVL(int num)
{
	if (avl->Search(num) != NULL) return avl->Search(num);
	else return NULL;
}

bool Manager::DELETE_AVL(int num)
{
	if (avl->Delete(num)) return true;
	else return false;
}

bool Manager::BUILD_GP()
{
	if (gp->Build(avl)) return true;
	else return false;
}

bool Manager::PRINT_GP()
{
	if (gp->mList != NULL) return true;
	else return false;
}

bool Manager::BUILD_MST()
{
	return true;
}

bool Manager::PRINT_MST()
{
	return true;
}

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