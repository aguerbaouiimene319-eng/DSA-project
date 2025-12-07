#ifndef LOANLIST_H
#define LOANLIST_H

#include"Loan.h"
#include<iostream>

struct Nodelist {
	loan data;
	Nodelist* next;
	Nodelist* prev;
};

struct LoanList {
	Nodelist* head = nullptr;
	Nodelist* tail = nullptr;
};

#endif // !LOANLIST_H
