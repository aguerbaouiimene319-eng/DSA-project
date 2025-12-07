#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include"Date.h"
#include<iostream>
#include<string>
using namespace std;

struct employee {
	string ID;
	string name;
	string LastName;
	string address;
	float salary;
	date HireDate;
	string BankBranch;//code of branch or 1 for head office
};
#endif