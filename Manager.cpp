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
			//call function()
			//example. ( you have to change )
			if (LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100, "LOAD");
		}
		else if (!strcmp(one, "INSERT")) {
			//call function()
		}
		else if (!strcmp(one, "PRINT_AVL")) {
			//call function()
			if (PRINT_AVL()) printSuccessCode("PRINT_AVL");
			else printErrorCode(300, "PRINT_AVL");
		}
		else if (!strcmp(one, "SEARCH_AVL")) {
			//call function()
		}
		else if (!strcmp(one, "DELETE_AVL")) {
			//call function()
		}
		else if (!strcmp(one, "BUILD_GP")) {
			//call function()
		}
		else if (!strcmp(one, "PRINT_GP")) {
			//call function()
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

bool Manager::INSERT()
{
	return true;
}

bool Manager::PRINT_AVL()
{
	if (avl->Print()) return true;
	else return false;
}

bool Manager::SEARCH_AVL()
{
	return true;
}

bool Manager::DELETE_AVL()
{
	return true;
}

bool Manager::BUILD_GP()
{
	return true;
}

bool Manager::PRINT_GP()
{
	return true;
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