#ifndef LOAN_H
#define LOAN_H
#include<iostream>
using namespace std;

struct loan {
	int ID;
	string LoanType;
	float amount;
	float InterestRate;
	float AmPaid;
	float ReBalance;
	string StartDate;
	string EndDate;
	string LoanStatus;
};

struct Node {
	loan data;
	Node* next;
	Node* prev;
};

struct LoanList {
	Node* head;
	Node* tail;
	int size;
};
#endif