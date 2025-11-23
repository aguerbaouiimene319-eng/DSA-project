
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<string>
using namespace std;

struct transaction {
	int ID;
	int AccountNum;
	string TransType;
	float Amount;
	string TransDate;
};

#endif