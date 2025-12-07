#ifndef LOAN_H
#define LOAN_H
#include<iostream>
#include<string>
#include"Date.h"
using namespace std;

struct loan {
	int ID;
	string type;// home,student,bussiness
	float amount;
	float InterestRate;
	float AmPaid;
	float ReBalance;
	date StartDate;
	date EndDate;
	string LoanStatus;//active,completed,overdue

};
#endif