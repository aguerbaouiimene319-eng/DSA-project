#ifndef COMPLETEDLOANLIST_H
#define COMPLETEDLOANLIST_H
#include"Loan.h"
#include<iostream>
using namespace std;

struct NodeCompLoan {
	loan data;
	NodeCompLoan* next;
};
struct CompList {
	NodeCompLoan* head;
};
#endif