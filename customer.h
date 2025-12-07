#ifndef CUSTOMER_H
#define CUSTOMER_H

#include"Date.h"
#include"LoanListMeth.h"
#include"TransactionStackMeth.h"
using namespace std;

struct customer {
	string passwrd;
	int AccNum;
	string AccType;
	int IBAN;
	int Branch;
	string name;
	date OpDate;
	string status;//active,inactive,closed
	float balance;
	LoanList loans;
	stack transList;

};
#endif