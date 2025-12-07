#ifndef LOANREQUEST_H
#define LOANREQUEST_H
#include <iostream>
#include"customer.h"
#include"Date.h"
using namespace std;

struct Node {
	LoanRequest data;
	Node* next;
};

struct queue {
	Node* front; //ptr to 1 st element
	Node* tail; //ptr to  st element
};
struct LoanRequest {
	int requestAccNumber;
	string loanType;
	double PrincipleAmount;
	date StartDate;
	date EndDate;
	date RequestDate;
};

#endif