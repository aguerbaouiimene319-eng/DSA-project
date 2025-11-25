#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>
#include"DoublyLinkedList.h"
#include"loan.h";
using namespace std;

struct customer {
	string passwrd;
	int AccNum;
	string AccType;
	int IBAN;
	int Branch;
	string name;
	string OpDate;
	string statute;
	float balance;
	LoanList loan;
};
#endif
