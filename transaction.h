#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<iostream>
#include<string>
#include"Date.h"

using namespace std;

struct transaction {
	int ID;
	int AccountNum;
	string TransType;//deposit or withdrawl
	double Amount;
	date TransDate;
};
//StackContigMeth<transaction>dailyTransactions;

#endif 